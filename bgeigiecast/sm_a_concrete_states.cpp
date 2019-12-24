#include "sm_a_concrete_states.h"

// region ApiProcessReadingState

ApiProcessReadingState::ApiProcessReadingState(IApiConnector& context, Reading& reading)
    : ApiReporterState(context), _reading(reading) {}

void ApiProcessReadingState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Process");
#endif
}

void ApiProcessReadingState::do_activity() {
  api_connector.process_reading(_reading);
}

void ApiProcessReadingState::exit_action() {}

void ApiProcessReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_report_reading:
      api_connector.set_state(new ConnectWiFiState(api_connector));
      break;
    case e_a_not_reporting:
      api_connector.set_state(new ApiReportDoneState(api_connector, IApiConnector::k_report_skipped));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region ConnectWiFiState


#define RETRY_CONNECTION 1000
#define CONNECTION_TIMEOUT 3000

ConnectWiFiState::ConnectWiFiState(IApiConnector& context)
    : ApiReporterState(context), _start_time(0), _last_connect_try(0) {}

void ConnectWiFiState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Connecting");
#endif
  api_connector.start_connect(true);
  _start_time = millis();
  _last_connect_try = millis();
}

void ConnectWiFiState::do_activity() {
  if(api_connector.is_connected()) {
    api_connector.schedule_event(e_a_wifi_connected);
  } else if(millis() - _last_connect_try > RETRY_CONNECTION) {
    _last_connect_try = millis();
    api_connector.start_connect(false);
  } else if(millis() - _start_time > CONNECTION_TIMEOUT) {
    api_connector.schedule_event(e_a_wifi_connection_error);
  }
}

void ConnectWiFiState::exit_action() {}

void ConnectWiFiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_wifi_connected:
      api_connector.set_state(new PublishApiState(api_connector));
      break;
    case e_a_wifi_connection_error:
      api_connector.set_state(new ApiReportFailedState(api_connector));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region PublishApiState

PublishApiState::PublishApiState(IApiConnector& context) : ApiReporterState(context) {}

void PublishApiState::entry_action() {}

void PublishApiState::do_activity() {
  api_connector.send_reading();
}

void PublishApiState::exit_action() {}

void PublishApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_api_post_failed:
      api_connector.set_state(new ApiReportFailedState(api_connector));
      break;
    case e_a_reading_posted:
      if(api_connector._saved_readings.get_count() > 0) {
        api_connector._merged_reading = api_connector._saved_readings.get();
        api_connector.set_state(new PublishApiState(api_connector));
      } else {
        api_connector.set_state(new ApiReportDoneState(api_connector, IApiConnector::k_report_success));
      }
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region ApiReportFailedState

ApiReportFailedState::ApiReportFailedState(IApiConnector& context) : ApiReporterState(context) {}

void ApiReportFailedState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Failed");
#endif
}

void ApiReportFailedState::do_activity() {
  api_connector.save_reading();
}

void ApiReportFailedState::exit_action() {}

void ApiReportFailedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_reading_saved:
      api_connector.set_state(new ApiReportDoneState(api_connector, IApiConnector::k_report_failed));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region ApiReportDoneState

ApiReportDoneState::ApiReportDoneState(IApiConnector& context, IApiConnector::ReportApiStatus status)
    : ApiReporterState(context), status(status) {}

void ApiReportDoneState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Done");
#endif
  if(status == IApiConnector::k_report_failed || status == IApiConnector::k_report_success) {
    api_connector._merged_reading.reset();
  }
  if(api_connector._observer) {
    api_connector._observer->api_reported(status);
  }
}

void ApiReportDoneState::do_activity() {}

void ApiReportDoneState::exit_action() {}

void ApiReportDoneState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion
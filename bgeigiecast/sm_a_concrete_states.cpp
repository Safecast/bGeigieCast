#include "sm_a_concrete_states.h"

// region ApiProcessReadingState

ApiProcessReadingState::ApiProcessReadingState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {}

void ApiProcessReadingState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Process");
#endif
}

void ApiProcessReadingState::do_activity() {
  api_connector.process_reading(reading);
}

void ApiProcessReadingState::exit_action() {}

void ApiProcessReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_report_reading:
      api_connector.set_state(new ConnectWiFiState(api_connector, &api_connector._merged_reading));
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


#define RETRY_EVERY 2000
#define CONNECTION_TIMEOUT 6000

ConnectWiFiState::ConnectWiFiState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading), _start_time(0), _last_connect_try(0) {}

void ConnectWiFiState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Connecting");
#endif
  api_connector.start_connect();
  _start_time = millis();
  _last_connect_try = millis();
}

void ConnectWiFiState::do_activity() {
  uint32_t current_time = millis();

  if(api_connector.is_connected()) {
    api_connector.schedule_event(e_a_wifi_connected);
  } else if(current_time - _last_connect_try > RETRY_EVERY) {
    api_connector.start_connect();
    _last_connect_try = _last_connect_try + RETRY_EVERY;
  } else if(current_time - _start_time > CONNECTION_TIMEOUT) {
    api_connector.schedule_event(e_a_wifi_connection_error);
  }
}

void ConnectWiFiState::exit_action() {}

void ConnectWiFiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_wifi_connected:
      if(!api_connector.api_endpoint_resolved()) {
        api_connector.set_state(new ResolveEndpointState(api_connector, reading));
      }
      else {
        api_connector.set_state(new PublishApiState(api_connector, reading));
      }
      break;
    case e_a_wifi_connection_error:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region ResolveEndpoint

ResolveEndpointState::ResolveEndpointState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {}

void ResolveEndpointState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Resolve endpoint");
#endif
}

void ResolveEndpointState::do_activity() {
  api_connector.retrieve_endpoint();
}

void ResolveEndpointState::exit_action() {}

void ResolveEndpointState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_endpoint_available:
      api_connector.set_state(new PublishApiState(api_connector, reading));
      break;
    case e_a_endpoint_unavailable:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region PublishApiState

PublishApiState::PublishApiState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {}

void PublishApiState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Publish api");
#endif
}

void PublishApiState::do_activity() {
  api_connector.send_reading(reading);
}

void PublishApiState::exit_action() {}

void PublishApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_api_post_failed:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    case e_a_reading_posted:
      if(api_connector._saved_readings.get_count() > 0) {
        Reading* next_saved = api_connector._saved_readings.get();
        api_connector.set_state(new PublishSavedApiState(api_connector, next_saved));
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

ApiReportFailedState::ApiReportFailedState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {}

void ApiReportFailedState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Failed");
#endif
}

void ApiReportFailedState::do_activity() {
  api_connector.save_reading(reading);
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

// region PublishSavedApiState

PublishSavedApiState::PublishSavedApiState(IApiConnector& context, Reading* reading) : PublishApiState(context, reading) {}

void PublishSavedApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_api_post_failed:
      api_connector.set_state(new ApiReportSavedFailedState(api_connector, reading));
      break;
    case e_a_reading_posted:
      PublishApiState::handle_event(event_id);
      delete reading;
      break;
    default:
      PublishApiState::handle_event(event_id);
      break;
  }
}

ApiReportSavedFailedState::ApiReportSavedFailedState(IApiConnector& context, Reading* reading) : ApiReportFailedState(context, reading) {}

void ApiReportSavedFailedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_reading_saved:
      ApiReportFailedState::handle_event(event_id);
      delete reading;
      break;
    default:
      ApiReportFailedState::handle_event(event_id);
      break;
  }
}

// endregion

// region ApiReportDoneState

ApiReportDoneState::ApiReportDoneState(IApiConnector& context, IApiConnector::ReportApiStatus status)
    : ApiReporterState(context, nullptr), status(status) {}

void ApiReportDoneState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("-- API entered state Done");
#endif
  if(status == IApiConnector::k_report_failed || status == IApiConnector::k_report_success) {
    api_connector._merged_reading.reset();
    api_connector.disconnect();
  }
  if(api_connector._observer) {
    api_connector._observer->api_reported(status);
  }
}

void ApiReportDoneState::do_activity() {
}

void ApiReportDoneState::exit_action() {
}

void ApiReportDoneState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

// endregion
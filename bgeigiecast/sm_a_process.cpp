#include "sm_a_process.h"
#include "sm_a_reporting_done.h"
#include "sm_a_connecting_wifi.h"

ApiProcessReadingState::ApiProcessReadingState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {

}

void ApiProcessReadingState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Apiconn entered state Process");
#endif
}

void ApiProcessReadingState::do_activity() {
  api_connector.process_reading(reading);
}

void ApiProcessReadingState::exit_action() {

}

void ApiProcessReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_report_reading:
      api_connector.set_state(new ConnectWiFiState(api_connector, reading));
      break;
    case e_a_not_reporting:
      api_connector.set_state(new ApiReportDoneState(api_connector, IApiConnector::k_report_skipped));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}
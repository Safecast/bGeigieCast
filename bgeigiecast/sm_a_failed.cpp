#include "sm_a_failed.h"
#include "sm_a_reporting_done.h"

ApiReportFailedState::ApiReportFailedState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {
}

void ApiReportFailedState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Apiconn entered state Failed");
#endif
}

void ApiReportFailedState::do_activity() {
  api_connector.save_reading(reading);
}

void ApiReportFailedState::exit_action() {
}

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
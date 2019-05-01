#include "sm_a_reporting_done.h"

ApiReportDoneState::ApiReportDoneState(IApiConnector& context, IApiConnector::ReportApiStatus status)
    : ApiReporterState(context, nullptr), status(status) {

}

void ApiReportDoneState::entry_action() {
  DEBUG_PRINTLN("Apiconn entered state Done");
  if(status == IApiConnector::k_report_failed || status == IApiConnector::k_report_success) {
    api_connector._merged_reading.reset();
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

#include "sm_a_reporting_done.h"


ApiReportDoneState::ApiReportDoneState(IApiConnector& context, IApiConnector::ReportApiStatus status)
    : ApiReporterState(context, nullptr), status(status) {

}

void ApiReportDoneState::entry_action() {
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

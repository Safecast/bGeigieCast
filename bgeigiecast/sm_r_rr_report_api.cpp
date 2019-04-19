#include "sm_r_rr_report_api.h"
#include "sm_r_rr_done.h"

ReportApiState::ReportApiState(Reporter& context) : ReportReadingState(context) {
}

void ReportApiState::entry_action() {
}

void ReportApiState::do_activity() {
}

void ReportApiState::exit_action() {
}

void ReportApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported_api_success:
      reporter.set_state(new ReporterDoneState(reporter, Reporter::k_reporter_success));
      break;
    case e_r_reading_reported_api_failed:
      reporter.set_state(new ReporterDoneState(reporter, Reporter::k_reporter_failed));
      break;
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

#include "sm_r_rr_done.h"
#include "sm_r_idle.h"

ReporterDoneState::ReporterDoneState(Reporter& context, Reporter::ReporterStatus status) : ReportReadingState(context), status(status) {

}

void ReporterDoneState::entry_action() {
  DEBUG_PRINTLN("Reporter entered state Done");
}

void ReporterDoneState::do_activity() {
  reporter.report_complete(status);
}

void ReporterDoneState::exit_action() {

}

void ReporterDoneState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}
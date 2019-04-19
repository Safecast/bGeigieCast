#include "sm_r_rr_done.h"
#include "sm_r_idle.h"

ReporterDoneState::ReporterDoneState(Reporter& context, Reporter::ReporterStatus status) : ReportReadingState(context), status(status) {

}

void ReporterDoneState::entry_action() {

}

void ReporterDoneState::do_activity() {

}

void ReporterDoneState::exit_action() {

}

void ReporterDoneState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported:
      reporter.set_state(new ReporterIdleState(reporter));
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}
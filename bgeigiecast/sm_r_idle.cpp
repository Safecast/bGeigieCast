#include "sm_r_idle.h"
#include "sm_r_get_reading.h"

ReporterIdleState::ReporterIdleState(Reporter& context) : ReporterState(context) {
}

void ReporterIdleState::entry_action() {
  DEBUG_PRINTLN("Reporter entered state Idle");
}

void ReporterIdleState::do_activity() {
  if(reporter.time_till_next_reading(millis()) == 0){
    reporter.schedule_event(e_r_reading_expected);
  }
}

void ReporterIdleState::exit_action() {

}

void ReporterIdleState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_expected:
      reporter.set_state(new GetReadingState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

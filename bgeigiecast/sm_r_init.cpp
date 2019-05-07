#include "sm_r_init.h"
#include "sm_r_idle.h"

InitReporterState::InitReporterState(Reporter& context) : ReporterState(context) {

}

void InitReporterState::entry_action() {
  DEBUG_PRINTLN("Reporter entered state Init");
}

void InitReporterState::do_activity() {
  reporter.get_new_reading();
}

void InitReporterState::exit_action() {
}

void InitReporterState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_received:
      reporter.set_state(new ReporterIdleState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}


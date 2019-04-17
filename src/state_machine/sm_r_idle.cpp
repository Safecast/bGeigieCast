#include "sm_r_idle.h"

IdleState::IdleState(Reporter& context) : ReporterState(context) {
}

void IdleState::entry_action() {

}

void IdleState::do_activity() {

}

void IdleState::exit_action() {

}

void IdleState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

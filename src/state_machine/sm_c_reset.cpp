#include "sm_c_reset.h"
#include "sm_c_init.h"

ResetState::ResetState(Controller& context) : ControllerState(context) {

}

void ResetState::entry_action() {
  DEBUG_PRINTLN("Entered state Reset");
}

void ResetState::do_activity() {
  controller.reset_system();
}

void ResetState::exit_action() {

}

void ResetState::handle_event(Event_enum event_id) {
  ControllerState::handle_event(event_id);
}

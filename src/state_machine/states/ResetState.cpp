#include "ResetState.hpp"
#include "InitializeState.h"

ResetState::ResetState(Controller& context) : State(context) {

}

void ResetState::entry_action() {
  debug_println("Entered state Reset");
}

void ResetState::do_activity() {
  controller.get_config().reset_defaults();
  controller.set_state(new InitializeState(controller));
}

void ResetState::exit_action() {

}

void ResetState::handle_event(Event_enum event_id) {
  State::handle_event(event_id);
}

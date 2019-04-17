#include "ResetState__.hpp"
#include "InitializeState__.h"

ResetState__::ResetState__(Controller& context) : State(context) {

}

void ResetState__::entry_action() {
  debug_println("Entered state Reset");
}

void ResetState__::do_activity() {
  controller.get_config().reset_defaults();
  debug_println("\n RESTARTING ESP...\n");
  ESP.restart();
}

void ResetState__::exit_action() {

}

void ResetState__::handle_event(Event_enum event_id) {
  State::handle_event(event_id);
}

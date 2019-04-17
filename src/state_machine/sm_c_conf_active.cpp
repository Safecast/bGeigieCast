#include "active_states/stationary_mode_states/ConnectingState__.h"
#include "ServerActiveState__.hpp"

ServerActiveState__::ServerActiveState__(Controller& context): State(context) {
}

void ServerActiveState__::entry_action() {
  debug_println("Entered state ServerActive");
}

void ServerActiveState__::do_activity() {
  controller.get_ap_server().handle_requests();
}

void ServerActiveState__::exit_action() {
  controller.get_ap_server().stop();
}

void ServerActiveState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.set_state(new ConnectingState__(controller));
      break;
    default:
      State::handle_event(event_id);
      break;
  }
}

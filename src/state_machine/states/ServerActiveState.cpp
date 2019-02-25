#include "active_states/MobileModeState.h"
#include "ServerActiveState.hpp"

ServerActiveState::ServerActiveState(Controller& context): State(context) {
}

void ServerActiveState::entry_action() {
  debug_println("Entered state ServerActive");
}

void ServerActiveState::do_activity() {
  controller.get_ap_server().handle_requests();
}

void ServerActiveState::exit_action() {
  controller.get_ap_server().stop();
}

void ServerActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.set_state(new MobileModeState(controller));
      break;
    default:
      State::handle_event(event_id);
      break;
  }
}

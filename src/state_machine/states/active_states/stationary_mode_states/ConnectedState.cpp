#include "ConnectedState.h"
#include "ConnectionErrorState.h"

ConnectedState::ConnectedState(Controller& context): StationaryModeState(context) {
}

void ConnectedState::entry_action() {
  debug_println("Entered state Connected");
  controller.get_state_led().set_state_led(StateLED::StateColor::stationary_active);
}

void ConnectedState::do_activity() {
  StationaryModeState::do_activity();
}

void ConnectedState::exit_action() {
}

void ConnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_connection_lost:
      controller.set_state(new ConnectionErrorState(controller));
      break;
    default:
      StationaryModeState::handle_event(event_id);
      break;
  }
}

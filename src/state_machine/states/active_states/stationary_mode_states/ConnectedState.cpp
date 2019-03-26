#include "ConnectedState.h"
#include "ReconnectingState.h"

ConnectedState::ConnectedState(Controller& context): StationaryModeState(context) {
}

void ConnectedState::entry_action() {
  debug_println("Entered state Connected");
  controller.get_state_led().set_color(StateLED::StateColor::stationary_active);
}

void ConnectedState::do_activity() {
  StationaryModeState::do_activity();
  if(!controller.get_api_connector().is_connected()){
    controller.schedule_event(Event_enum::e_connection_lost);
  }
}

void ConnectedState::exit_action() {
}

void ConnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_connection_lost:
      controller.set_state(new ReconnectingState(controller));
      break;
    default:
      StationaryModeState::handle_event(event_id);
      break;
  }
}

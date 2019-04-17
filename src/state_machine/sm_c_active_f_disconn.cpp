#include "ConnectingState.h"
#include "TestApiState.h"
#include "ConnectionErrorState.h"

#define MILLIS_BEFORE_CONNECTION_FAILURE 6000

#define CONNECTING_BLINK_FREQUENCY_MILLIS 2100

ConnectingState::ConnectingState(Controller& context): StationaryModeState(context), state_entry_moment(0) {
}

void ConnectingState::entry_action() {
  debug_println("Entered state Connecting");
  controller.get_state_led().set_color(StateLED::StateColor::stationary_connecting);
  state_entry_moment = millis();
  controller.get_api_connector().start_connect(true);
}

void ConnectingState::do_activity() {
  StationaryModeState::do_activity();
  if(controller.get_api_connector().is_connected()) {
    controller.schedule_event(Event_enum::e_connected);
  }
  else if (millis() - state_entry_moment > MILLIS_BEFORE_CONNECTION_FAILURE) {
    controller.schedule_event(e_connection_failed);
  }

  controller.get_state_led().blink(StateLED::StateColor::stationary_connecting, CONNECTING_BLINK_FREQUENCY_MILLIS);
}

void ConnectingState::exit_action() {
}

void ConnectingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_connected:
      controller.set_state(new TestApiState(controller));
      break;
    case e_connection_failed:
      controller.set_state(new ConnectionErrorState(controller));
      break;
    default:
      StationaryModeState::handle_event(event_id);
      break;
  }
}

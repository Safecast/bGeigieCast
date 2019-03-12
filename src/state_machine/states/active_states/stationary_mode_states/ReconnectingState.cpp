#include "ReconnectingState.h"
#include "TestApiState.h"
#include "ConnectionErrorState.h"

// connection error after 30 seconds of not being able to reconnect
#define MILLIS_BEFORE_CONNECTION_FAILURE 30000

#define CONNECTING_BLINK_FREQUENCY_MILLIS 500

ReconnectingState::ReconnectingState(Controller& context): StationaryModeState(context), timer(0) {
}

void ReconnectingState::entry_action() {
  debug_println("Entered state Connecting");
  controller.get_state_led().set_state_led(StateLED::StateColor::stationary_connecting);
  timer = millis();
}

void ReconnectingState::do_activity() {
  StationaryModeState::do_activity();
  if(!((millis() - timer) % 5000) && controller.get_api_connector().start_connect(false)) {
    controller.schedule_event(Event_enum::e_connected);
  }
  else if (millis() > timer + MILLIS_BEFORE_CONNECTION_FAILURE) {
    controller.schedule_event(e_connection_failed);
  }

  controller.get_state_led().blink(StateLED::StateColor::stationary_connecting, CONNECTING_BLINK_FREQUENCY_MILLIS);
}

void ReconnectingState::exit_action() {
}

void ReconnectingState::handle_event(Event_enum event_id) {
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

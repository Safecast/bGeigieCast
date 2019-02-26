#include "ConnectingState.h"
#include "TestApiState.h"
#include "ConnectionErrorState.h"

ConnectingState::ConnectingState(Controller& context): StationaryModeState(context), timer(0) {
}

void ConnectingState::entry_action() {
  debug_println("Entered state Connecting");
  timer = millis();
  controller.get_api_connector().start_connect();
}

void ConnectingState::do_activity() {
  if(controller.get_api_connector().is_connected()) {
    controller.schedule_event(Event_enum::e_connected);
  }
  else if (millis() > timer + MILLIS_BEFORE_CONNECTION_FAILURE) {
    controller.schedule_event(e_connection_failed);
  }
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

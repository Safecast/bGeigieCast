#include "ConnectionErrorState.h"
#include "TestApiState.h"

ConnectionErrorState::ConnectionErrorState(Controller& context): StationaryModeState(context), timer(0) {
}

void ConnectionErrorState::entry_action() {
  debug_println("Entered state ConnectionError");
  timer = millis();
}

void ConnectionErrorState::do_activity() {
  if(!((millis() - timer) % 5000) && controller.get_api_connector().start_connect()) {
    controller.schedule_event(Event_enum::e_connected);
  }
}

void ConnectionErrorState::exit_action() {
}

void ConnectionErrorState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_connected:
      controller.set_state(new TestApiState(controller));
      break;
    default:
      StationaryModeState::handle_event(event_id);
      break;
  }
}

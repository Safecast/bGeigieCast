#include "ConnectionErrorState.h"
#include "TestApiState.h"

#define BLINK_FREQUENCY_MILLIS 1000

ConnectionErrorState::ConnectionErrorState(Controller& context) : StationaryModeState(context), timer(0), blink_state(false) {
}

void ConnectionErrorState::entry_action() {
  debug_println("Entered state ConnectionError");
  controller.get_state_led().set_color(StateLED::StateColor::stationary_error);
  timer = millis();
}

void ConnectionErrorState::do_activity() {
  StationaryModeState::do_activity();
  if(!((millis() - timer) % 5000) && controller.get_api_connector().start_connect(false)) {
    controller.schedule_event(Event_enum::e_connected);
  }

  controller.get_state_led().blink(StateLED::StateColor::stationary_error, BLINK_FREQUENCY_MILLIS);
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

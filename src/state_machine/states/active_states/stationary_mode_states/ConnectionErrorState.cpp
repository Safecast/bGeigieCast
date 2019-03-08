#include "ConnectionErrorState.h"
#include "TestApiState.h"

#define BLINK_FREQUENCY_MILLIS 500

ConnectionErrorState::ConnectionErrorState(Controller& context) : StationaryModeState(context), timer(0), blink_state(false) {
}

void ConnectionErrorState::entry_action() {
  debug_println("Entered state ConnectionError");
  controller.get_state_led().set_state_led(StateLED::StateColor::stationary_error);
  timer = millis();
}

void ConnectionErrorState::do_activity() {
  StationaryModeState::do_activity();
  if(!((millis() - timer) % 5000) && controller.get_api_connector().start_connect()) {
    controller.schedule_event(Event_enum::e_connected);
  }
  // Blink LED
  if(timer % BLINK_FREQUENCY_MILLIS > BLINK_FREQUENCY_MILLIS / 2 && !blink_state) {
    controller.get_state_led().set_state_led(StateLED::StateColor::stationary_error);
    blink_state = true;
  } else if(timer % BLINK_FREQUENCY_MILLIS < BLINK_FREQUENCY_MILLIS / 2 && blink_state){
    controller.get_state_led().set_state_led(StateLED::StateColor::off);
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

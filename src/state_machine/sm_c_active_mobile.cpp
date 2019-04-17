#include "MobileModeState__.h"
#include "stationary_mode_states/ConnectingState__.h"

MobileModeState__::MobileModeState__(Controller& context): ActiveState__(context) {
}

void MobileModeState__::entry_action() {
  debug_println("Entered state MobileMode");
  controller.get_state_led().set_color(StateLED::StateColor::mobile);
}

void MobileModeState__::do_activity() {
  controller.process_possible_bgeigie_readings(true, false);
}

void MobileModeState__::exit_action() {
}

void MobileModeState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.set_state(new ConnectingState__(controller));
      break;
    default:
      ActiveState__::handle_event(event_id);
      break;
  }
}

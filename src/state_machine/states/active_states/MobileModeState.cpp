#include "MobileModeState.h"
#include "stationary_mode_states/ConnectingState.h"

MobileModeState::MobileModeState(Controller& context): ActiveState(context) {
}

void MobileModeState::entry_action() {
  debug_println("Entered state MobileMode");
}

void MobileModeState::do_activity() {
  controller.process_possible_bgeigie_readings(true, false);
}

void MobileModeState::exit_action() {
}

void MobileModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.set_state(new ConnectingState(controller));
      break;
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

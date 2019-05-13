#include "sm_c_active_mobile.h"
#include "sm_c_active_f_disconn.h"

MobileModeState::MobileModeState(Controller& context): ActiveState(context) {
}

void MobileModeState::entry_action() {
  DEBUG_PRINTLN("Entered state MobileMode");
  controller.save_state(k_savable_MobileMode);
  controller._state_led.set_color(StateLED::StateColor::mobile);
  controller.set_reporter_outputs(true, false);
}

void MobileModeState::do_activity() {
  ActiveState::do_activity();
}

void MobileModeState::exit_action() {
}

void MobileModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new DisconnectedState(controller));
      break;
    case e_c_report_success:
      // Success, no need to do anything
      break;
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

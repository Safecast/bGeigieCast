#include "sm_c_active_fixed.h"
#include "sm_c_active_mobile.h"

FixedModeState::FixedModeState(Controller& context) : ActiveState(context) {
}

void FixedModeState::do_activity() {
  ActiveState::do_activity();
}

void FixedModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.set_state(new MobileModeState(controller));
      break;
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

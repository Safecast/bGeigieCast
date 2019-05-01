#include "sm_c_active.h"
#include "sm_c_reset.h"

ActiveState::ActiveState(Controller& context): ControllerState(context) {
}

void ActiveState::do_activity() {
  controller.sleep();
  controller.run_reporter();
}

void ActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_long_pressed:
      controller.set_state(new ResetState(controller));
      break;
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

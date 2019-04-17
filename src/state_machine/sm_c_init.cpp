#include "sm_c_init.h"
#include "sm_events.h"
#include "sm_c_post_init.h"

InitializeState::InitializeState(Controller& context) : ControllerState(context) {
}

void InitializeState::entry_action() {
  DEBUG_PRINTLN("Entered state Initialize");
  controller.get_state_led().set_color(StateLED::StateColor::init);
}

void InitializeState::do_activity() {
  controller.initialize();
}

void InitializeState::exit_action() {

}

void InitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_controller_initialized: {
      controller.set_state(new PostInitializeState(controller));
      break;
    }
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}
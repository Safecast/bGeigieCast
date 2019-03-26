#include "PostInitializeState.h"
#include "SetupServerState.hpp"
#include "active_states/MobileModeState.h"
#include "active_states/stationary_mode_states/ConnectingState.h"

#define POST_INIT_DURATION_MILLIS 3000

PostInitializeState::PostInitializeState(Controller& context) : State(context), timer(0) {
}

void PostInitializeState::entry_action() {
  debug_println("Entered state PostInitialize");
  controller.get_state_led().set_state_led(StateLED::StateColor::init);
  timer = millis();
}

void PostInitializeState::do_activity() {
  if(millis() - timer > POST_INIT_DURATION_MILLIS) {
    controller.schedule_event(e_post_init_time_passed);
  }
}

void PostInitializeState::exit_action() {

}

void PostInitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed: {
      controller.set_state(new SetupServerState(controller));
      break;
    }
    case e_post_init_time_passed: {
      if (controller.get_config().is_init_stationary())
        controller.set_state(new ConnectingState(controller));
      else
        controller.set_state(new MobileModeState(controller));
      break;
    }
    default:
      State::handle_event(event_id);
      break;
  }
}


#include "PostInitializeState__.h"
#include "SetupServerState__.hpp"
#include "active_states/MobileModeState__.h"
#include "active_states/stationary_mode_states/ConnectingState__.h"

#define POST_INIT_DURATION_MILLIS 3000

PostInitializeState__::PostInitializeState__(Controller& context) : State(context), timer(0) {
}

void PostInitializeState__::entry_action() {
  debug_println("Entered state PostInitialize");
  controller.get_state_led().set_color(StateLED::StateColor::init);
  timer = millis();
}

void PostInitializeState__::do_activity() {
  if(millis() - timer > POST_INIT_DURATION_MILLIS) {
    controller.schedule_event(e_post_init_time_passed);
  }
}

void PostInitializeState__::exit_action() {

}

void PostInitializeState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed: {
      controller.set_state(new SetupServerState__(controller));
      break;
    }
    case e_post_init_time_passed: {
      if (controller.get_config().is_init_stationary())
        controller.set_state(new ConnectingState__(controller));
      else
        controller.set_state(new MobileModeState__(controller));
      break;
    }
    default:
      State::handle_event(event_id);
      break;
  }
}


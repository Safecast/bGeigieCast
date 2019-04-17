#include "sm_c_post_init.h"
#include "sm_c_conf_setup.h"
#include "sm_c_active_f_disconn.h"
#include "sm_c_active_mobile.h"
#include "sm_c_active_init.h"

#define POST_INIT_DURATION_MILLIS 3000

PostInitializeState::PostInitializeState(Controller& context) : ControllerState(context), timer(0) {
}

void PostInitializeState::entry_action() {
  DEBUG_PRINTLN("Entered state PostInitialize");
  controller.get_state_led().set_color(StateLED::StateColor::init);
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
    case e_button_pressed:
      controller.set_state(new SetupServerState(controller));
      break;
    case e_post_init_time_passed:
      controller.set_state(new InitActiveState(controller));
      break;
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}


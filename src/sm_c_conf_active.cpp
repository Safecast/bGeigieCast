#include "sm_c_conf_active.h"
#include "sm_c_active_f_disconn.h"
#include "sm_c_active_init.h"

ServerActiveState::ServerActiveState(Controller& context) : ConfigModeState(context) {
}

void ServerActiveState::entry_action() {
  DEBUG_PRINTLN("Entered state ServerActive");
}

void ServerActiveState::do_activity() {
  controller.get_ap_server().handle_requests();
}

void ServerActiveState::exit_action() {
  controller.get_ap_server().stop();
}

void ServerActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.set_state(new InitActiveState(controller));
      break;
    default:
      ConfigModeState::handle_event(event_id);
      break;
  }
}

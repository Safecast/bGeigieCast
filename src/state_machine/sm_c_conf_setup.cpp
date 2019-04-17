#include "sm_c_conf_setup.h"
#include "sm_c_conf_active.h"

SetupServerState::SetupServerState(Controller& context) : ConfigModeState(context) {
}

void SetupServerState::entry_action() {
  DEBUG_PRINTLN("Entered state SetupServer");
  controller.get_state_led().set_color(StateLED::StateColor::config);
}

void SetupServerState::do_activity() {
  if(controller.get_ap_server().initialize()) {
    controller.schedule_event(Event_enum::e_server_initialized);
  }
}

void SetupServerState::exit_action() {
}

void SetupServerState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_server_initialized:
      controller.set_state(new ServerActiveState(controller));
      break;
    default:
      ConfigModeState::handle_event(event_id);
      break;
  }
}
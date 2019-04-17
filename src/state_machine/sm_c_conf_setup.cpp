#include "SetupServerState__.hpp"
#include "ServerActiveState__.hpp"

SetupServerState__::SetupServerState__(Controller& context) : State(context) {
}

void SetupServerState__::entry_action() {
  debug_println("Entered state SetupServer");
  controller.get_state_led().set_color(StateLED::StateColor::config);
}

void SetupServerState__::do_activity() {
  if(controller.get_ap_server().initialize()) {
    controller.schedule_event(Event_enum::e_server_initialized);
  }
}

void SetupServerState__::exit_action() {
}

void SetupServerState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_server_initialized:
      controller.set_state(new ServerActiveState__(controller));
      break;
    default:
      State::handle_event(event_id);
      break;
  }
}

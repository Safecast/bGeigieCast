#include "SetupServerState.hpp"
#include "ServerActiveState.hpp"

SetupServerState::SetupServerState(Controller& context) : State(context) {
}

void SetupServerState::entry_action() {
  debug_println("Entered state SetupServer");
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
      State::handle_event(event_id);
      break;
  }
}

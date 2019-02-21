#include "InitializeState.h"
#include "SetupServerState.hpp"

InitializeState::InitializeState(Controller& context): State(context) {
}

void InitializeState::entry_action() {
  debug_println("Entered state Initialize");
}

void InitializeState::do_activity() {
  controller.initialize();
}

void InitializeState::exit_action() {

}

void InitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_controller_initialized:
//      if(controller.)
      controller.set_state(new SetupServerState(controller));
      break;
    default:
      State::handle_event(event_id);
      break;
  }
}

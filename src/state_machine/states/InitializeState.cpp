#include "state_machine/states/active_states/MobileModeState.h"
#include "InitializeState.h"
#include "SetupServerState.hpp"

InitializeState::InitializeState(Controller& context) : State(context) {
}

void InitializeState::entry_action() {
  debug_println("Entered state Initialize");
  controller.get_state_led().set_state_led(StateLED::StateColor::init);
}

void InitializeState::do_activity() {
  controller.initialize();
}

void InitializeState::exit_action() {

}

void InitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_controller_initialized: {
      if(controller.get_mode_button().currently_pressed()) {
        controller.set_state(new SetupServerState(controller));
      } else {
        controller.set_state(new MobileModeState(controller));
      }
      break;
    }
    default:
      State::handle_event(event_id);
      break;
  }
}

#include "InitializeState.h"
#include "PostInitializeState.h"

InitializeState::InitializeState(Controller& context) : State(context) {
}

void InitializeState::entry_action() {
  debug_println("Entered state Initialize");
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
      State::handle_event(event_id);
      break;
  }
}

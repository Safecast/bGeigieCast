#include "InitializeState__.h"
#include "PostInitializeState__.h"

InitializeState__::InitializeState__(Controller& context) : State(context) {
}

void InitializeState__::entry_action() {
  debug_println("Entered state Initialize");
  controller.get_state_led().set_color(StateLED::StateColor::init);
}

void InitializeState__::do_activity() {
  controller.initialize();
}

void InitializeState__::exit_action() {

}

void InitializeState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_controller_initialized: {
      controller.set_state(new PostInitializeState__(controller));
      break;
    }
    default:
      State::handle_event(event_id);
      break;
  }
}

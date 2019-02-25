#include "TestApiState.h"
#include "ConnectedState.h"

TestApiState::TestApiState(Controller& context): StationaryModeState(context) {
}

void TestApiState::entry_action() {
  debug_println("Entered state TestApi");
}

void TestApiState::do_activity() {
  if(controller.get_api_connector().test()) {
    controller.schedule_event(Event_enum::e_API_available);
  }
}

void TestApiState::exit_action() {
}

void TestApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_API_available:
      controller.set_state(new ConnectedState(controller));
      break;
    default:
      StationaryModeState::handle_event(event_id);
      break;
  }
}

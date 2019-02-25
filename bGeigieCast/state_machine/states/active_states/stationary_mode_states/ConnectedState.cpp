#include "ConnectedState.h"

ConnectedState::ConnectedState(Controller& context): StationaryModeState(context) {
}

void ConnectedState::entry_action() {
  debug_println("Entered state Connected");
}

void ConnectedState::do_activity() {
}

void ConnectedState::exit_action() {
}

void ConnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      StationaryModeState::handle_event(event_id);
      break;
  }
}

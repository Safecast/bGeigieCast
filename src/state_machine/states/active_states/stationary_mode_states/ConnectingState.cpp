#include "ConnectingState.h"

ConnectingState::ConnectingState(Controller& context): StationaryModeState(context) {
}
void ConnectingState::entry_action() {
  StationaryModeState::entry_action();
}
void ConnectingState::do_activity() {
  StationaryModeState::do_activity();
}
void ConnectingState::exit_action() {
  StationaryModeState::exit_action();
}
void ConnectingState::handle_event(Event_enum event_id) {
  StationaryModeState::handle_event(event_id);
}

#include "ConnectedState.h"

ConnectedState::ConnectedState(Controller& context): StationaryModeState(context) {
}
void ConnectedState::entry_action() {
  StationaryModeState::entry_action();
}
void ConnectedState::do_activity() {
  StationaryModeState::do_activity();
}
void ConnectedState::exit_action() {
  StationaryModeState::exit_action();
}
void ConnectedState::handle_event(Event_enum event_id) {
  StationaryModeState::handle_event(event_id);
}

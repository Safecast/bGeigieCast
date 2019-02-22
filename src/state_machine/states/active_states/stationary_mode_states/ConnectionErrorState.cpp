#include "ConnectionErrorState.h"

ConnectionErrorState::ConnectionErrorState(Controller& context): StationaryModeState(context) {
}
void ConnectionErrorState::entry_action() {
  StationaryModeState::entry_action();
}
void ConnectionErrorState::do_activity() {
  StationaryModeState::do_activity();
}
void ConnectionErrorState::exit_action() {
  StationaryModeState::exit_action();
}
void ConnectionErrorState::handle_event(Event_enum event_id) {
  StationaryModeState::handle_event(event_id);
}

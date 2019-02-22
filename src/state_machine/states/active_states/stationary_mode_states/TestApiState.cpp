#include "TestApiState.h"

TestApiState::TestApiState(Controller& context): StationaryModeState(context) {
}
void TestApiState::entry_action() {
  StationaryModeState::entry_action();
}
void TestApiState::do_activity() {
  StationaryModeState::do_activity();
}
void TestApiState::exit_action() {
  StationaryModeState::exit_action();
}
void TestApiState::handle_event(Event_enum event_id) {
  StationaryModeState::handle_event(event_id);
}

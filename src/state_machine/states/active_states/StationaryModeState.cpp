#include "StationaryModeState.h"

StationaryModeState::StationaryModeState(Controller& context): ActiveState(context) {
}
void StationaryModeState::entry_action() {

}
void StationaryModeState::do_activity() {

}
void StationaryModeState::exit_action() {

}
void StationaryModeState::handle_event(Event_enum event_id) {
  State::handle_event(event_id);
}

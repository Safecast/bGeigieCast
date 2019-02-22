#include "MobileModeState.h"

MobileModeState::MobileModeState(Controller& context): ActiveState(context) {
}
void MobileModeState::entry_action() {
  debug_println("Entered state MobileMode");
}
void MobileModeState::do_activity() {

}
void MobileModeState::exit_action() {

}
void MobileModeState::handle_event(Event_enum event_id) {
  State::handle_event(event_id);
}

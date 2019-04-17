#include "sm_r_rr_init_bluetooth.h"

InitBluetoothState::InitBluetoothState(Reporter& context) : ReportReadingState(context) {

}
void InitBluetoothState::entry_action() {

}
void InitBluetoothState::do_activity() {

}
void InitBluetoothState::exit_action() {

}
void InitBluetoothState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

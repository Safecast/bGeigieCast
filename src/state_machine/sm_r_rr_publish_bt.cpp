#include "sm_r_rr_publish_bt.h"

PublishBluetoothState::PublishBluetoothState(Reporter& context) : ReportReadingState(context) {

}
void PublishBluetoothState::entry_action() {

}
void PublishBluetoothState::do_activity() {

}
void PublishBluetoothState::exit_action() {

}
void PublishBluetoothState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

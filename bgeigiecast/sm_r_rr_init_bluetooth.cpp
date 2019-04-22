#include "sm_r_rr_init_bluetooth.h"
#include "sm_r_rr_publish_bt.h"

InitBluetoothState::InitBluetoothState(Reporter& context) : ReportReadingState(context) {

}
void InitBluetoothState::entry_action() {
  DEBUG_PRINTLN("Reporter entered state Init Bluetooth");
}

void InitBluetoothState::do_activity() {
  reporter.init_bluetooth_connector();
}

void InitBluetoothState::exit_action() {

}

void InitBluetoothState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_bluetooth_initialized:
      reporter.set_state(new PublishBluetoothState(reporter));
      break;
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

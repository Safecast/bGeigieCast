#include "sm_r_rr_publish_bt.h"
#include "sm_r_rr_done.h"
#include "sm_r_rr_init_api.h"

PublishBluetoothState::PublishBluetoothState(Reporter& context) : ReportReadingState(context) {
}

void PublishBluetoothState::entry_action() {
  DEBUG_PRINTLN("Reporter entered state Publish Bluetooth");
}

void PublishBluetoothState::do_activity() {
  reporter.run_bluetooth_connector();
}

void PublishBluetoothState::exit_action() {
}

void PublishBluetoothState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported_bt:
      if (reporter.is_report_api()) {
        reporter.set_state(new InitApiState(reporter));
      }
      else {
        reporter.set_state(new ReporterDoneState(reporter, Reporter::k_reporter_success));
      }
      break;
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

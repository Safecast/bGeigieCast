#include "sm_r_rr_publish_bt.h"
#include "sm_r_rr_done.h"
#include "sm_r_rr_report_api.h"

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
    case e_r_reading_reported_bt:
      if (reporter.is_report_api()) {
        reporter.set_state(new ReportApiState(reporter));
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

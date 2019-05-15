#include "sm_r_concrete_states.h"

// region ReporterIdleState

ReporterIdleState::ReporterIdleState(Reporter& context) : ReporterState(context) {
}

void ReporterIdleState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Idle");
#endif
}

void ReporterIdleState::do_activity() {
  if(reporter.time_till_next_reading(millis()) == 0){
    reporter.schedule_event(e_r_reading_expected);
  }
}

void ReporterIdleState::exit_action() {

}

void ReporterIdleState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_expected:
      reporter.set_state(new GetReadingState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region GetReadingState

GetReadingState::GetReadingState(Reporter& context) : ReporterState(context) {

}

void GetReadingState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Get reading");
#endif
}

void GetReadingState::do_activity() {
  reporter.get_new_reading();
}

void GetReadingState::exit_action() {
}

void GetReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_received:
      if(reporter._report_bt) {
        reporter.set_state(new InitBluetoothState(reporter));
      }else if(reporter._report_api) {
        reporter.set_state(new InitApiState(reporter));
      } else {
        reporter.set_state(new ReporterIdleState(reporter));
      }
      break;
    case e_r_reading_invalid:
      reporter.set_state(new ReporterIdleState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region ReportReadingState

ReportReadingState::ReportReadingState(Reporter& context) : ReporterState(context) {
}

void ReportReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported:
      reporter.set_state(new ReporterIdleState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

// endregion

// region InitBluetoothState

InitBluetoothState::InitBluetoothState(Reporter& context) : ReportReadingState(context) {

}
void InitBluetoothState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Init Bluetooth");
#endif
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

// endregion

// region PublishBluetoothState

PublishBluetoothState::PublishBluetoothState(Reporter& context) : ReportReadingState(context) {
}

void PublishBluetoothState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Publish Bluetooth");
#endif
}

void PublishBluetoothState::do_activity() {
  reporter.run_bluetooth_connector();
}

void PublishBluetoothState::exit_action() {
}

void PublishBluetoothState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported_bt:
      if (reporter._report_api) {
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

// endregion

// region InitApiState

InitApiState::InitApiState(Reporter& context) : ReportReadingState(context) {
}

void InitApiState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Init api");
#endif
}

void InitApiState::do_activity() {
  reporter.init_api_connector();
}

void InitApiState::exit_action() {
}

void InitApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_api_connector_initialized:
      reporter.set_state(new ReportApiState(reporter));
      break;
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

// endregion

// region ReportApiState

ReportApiState::ReportApiState(Reporter& context) : ReportReadingState(context) {
}

void ReportApiState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Publish Api");
#endif
}

void ReportApiState::do_activity() {
  reporter.run_api_connector();
}

void ReportApiState::exit_action() {
}

void ReportApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported_api_no_change:
      reporter.set_state(new ReporterDoneState(reporter, Reporter::k_reporter_no_change));
      break;
    case e_r_reading_reported_api_success:
      reporter.set_state(new ReporterDoneState(reporter, Reporter::k_reporter_success));
      break;
    case e_r_reading_reported_api_failed:
      reporter.set_state(new ReporterDoneState(reporter, Reporter::k_reporter_failed));
      break;
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

// endregion

// region ReporterDoneState

ReporterDoneState::ReporterDoneState(Reporter& context, Reporter::ReporterStatus status) : ReportReadingState(context), status(status) {

}

void ReporterDoneState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Done");
#endif
}

void ReporterDoneState::do_activity() {
  reporter.report_complete(status);
}

void ReporterDoneState::exit_action() {

}

void ReporterDoneState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

// endregion
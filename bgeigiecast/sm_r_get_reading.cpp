
#include "sm_r_get_reading.h"
#include "sm_r_rr_init_bluetooth.h"
#include "sm_r_idle.h"

GetReadingState::GetReadingState(Reporter& context) : ReporterState(context) {

}

void GetReadingState::entry_action() {
  DEBUG_PRINTLN("Reporter entered state Get reading");
}

void GetReadingState::do_activity() {
  reporter.get_new_reading();
}

void GetReadingState::exit_action() {
}

void GetReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_received:
      reporter.set_state(new InitBluetoothState(reporter));
      break;
    case e_r_reading_invalid:
      reporter.set_state(new ReporterIdleState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

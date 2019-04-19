
#include "sm_r_get_reading.h"
#include "sm_r_rr_init_bluetooth.h"

GetReadingState::GetReadingState(Reporter& context) : ReporterState(context) {

}

void GetReadingState::entry_action() {
}

void GetReadingState::do_activity() {
}

void GetReadingState::exit_action() {
}

void GetReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_received:
      reporter.set_state(new InitBluetoothState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

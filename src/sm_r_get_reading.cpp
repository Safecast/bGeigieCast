
#include "sm_r_get_reading.h"

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
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

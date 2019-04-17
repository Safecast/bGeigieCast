#include "sm_r_rr_test_connection.h"

TestConnectionState::TestConnectionState(Reporter& context) : ReportReadingState(context) {

}
void TestConnectionState::entry_action() {

}
void TestConnectionState::do_activity() {

}
void TestConnectionState::exit_action() {

}
void TestConnectionState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

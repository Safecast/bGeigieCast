#include "sm_a_test_connection.h"
#include "sm_a_failed.h"
#include "sm_a_publish_api.h"

TestConnectionState::TestConnectionState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {

}
void TestConnectionState::entry_action() {

}
void TestConnectionState::do_activity() {

}
void TestConnectionState::exit_action() {

}
void TestConnectionState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_api_available:
      api_connector.set_state(new PublishApiState(api_connector, reading));
      break;
    case e_a_api_unavailable:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

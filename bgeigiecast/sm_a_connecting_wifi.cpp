#include "sm_a_connecting_wifi.h"
#include "sm_a_test_connection.h"
#include "sm_a_failed.h"

ConnectWiFiState::ConnectWiFiState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {

}
void ConnectWiFiState::entry_action() {

}
void ConnectWiFiState::do_activity() {

}
void ConnectWiFiState::exit_action() {

}
void ConnectWiFiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_wifi_connected:
      api_connector.set_state(new TestConnectionState(api_connector, reading));
      break;
    case e_a_wifi_connection_error:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

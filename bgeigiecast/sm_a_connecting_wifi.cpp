#include "sm_a_connecting_wifi.h"
#include "sm_a_failed.h"
#include "sm_a_publish_api.h"

#define RETRY_CONNECTION 1000
#define CONNECTION_TIMEOUT 3000

ConnectWiFiState::ConnectWiFiState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading), _start_time(0), _last_connect_try(0) {

}

void ConnectWiFiState::entry_action() {
  DEBUG_PRINTLN("Apiconn entered state Connecting");
  api_connector.start_connect(true);
  _start_time = millis();
  _last_connect_try = millis();
}

void ConnectWiFiState::do_activity() {
  if(api_connector.is_connected()) {
    api_connector.schedule_event(e_a_wifi_connected);
  } else if(millis() - _last_connect_try > RETRY_CONNECTION) {
    _last_connect_try = millis();
    api_connector.start_connect(false);
  } else if(millis() - _start_time > CONNECTION_TIMEOUT) {
    api_connector.schedule_event(e_a_wifi_connection_error);
  }
}

void ConnectWiFiState::exit_action() {

}

void ConnectWiFiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_wifi_connected:
      api_connector.set_state(new PublishApiState(api_connector, reading));
      break;
    case e_a_wifi_connection_error:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}

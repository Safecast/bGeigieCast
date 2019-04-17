#include "sm_r_rr_connecting_wifi.h"

ConnectWiFiState::ConnectWiFiState(Reporter& context) : ReportReadingState(context) {

}
void ConnectWiFiState::entry_action() {

}
void ConnectWiFiState::do_activity() {

}
void ConnectWiFiState::exit_action() {

}
void ConnectWiFiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

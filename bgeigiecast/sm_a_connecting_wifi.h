#ifndef BGEIGIECAST_SM_R_RR_CONNECTING_WIFI_H
#define BGEIGIECAST_SM_R_RR_CONNECTING_WIFI_H

#include "sm_a_state.h"

class ConnectWiFiState : public ApiReporterState {
 public:
  explicit ConnectWiFiState(IApiConnector& context, Reading* reading);
  virtual ~ConnectWiFiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:
  uint32_t _start_time;
  uint32_t _last_connect_try;
};

#endif //BGEIGIECAST_SM_R_RR_CONNECTING_WIFI_H

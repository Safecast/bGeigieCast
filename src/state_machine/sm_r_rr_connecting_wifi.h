#ifndef BGEIGIECAST_SM_R_RR_CONNECTING_WIFI_H
#define BGEIGIECAST_SM_R_RR_CONNECTING_WIFI_H

#include "sm_r_report_reading.h"

class ConnectWiFiState : public ReportReadingState {
 public:
  explicit ConnectWiFiState(Reporter& context);
  virtual ~ConnectWiFiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_R_RR_CONNECTING_WIFI_H

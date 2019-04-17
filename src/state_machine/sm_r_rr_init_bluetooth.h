#ifndef BGEIGIECAST_SM_R_RR_INIT_BLUETOOTH_H
#define BGEIGIECAST_SM_R_RR_INIT_BLUETOOTH_H

#include "sm_r_report_reading.h"

class InitBluetoothState : public ReportReadingState {
 public:
  explicit InitBluetoothState(Reporter& context);
  virtual ~InitBluetoothState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_R_RR_INIT_BLUETOOTH_H

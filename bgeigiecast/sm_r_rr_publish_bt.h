#ifndef BGEIGIECAST_SM_R_RR_PUBLISH_BT_H
#define BGEIGIECAST_SM_R_RR_PUBLISH_BT_H

#include "sm_r_report_reading.h"

class PublishBluetoothState : public ReportReadingState {
 public:
  explicit PublishBluetoothState(Reporter& context);
  virtual ~PublishBluetoothState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_R_RR_PUBLISH_BT_H

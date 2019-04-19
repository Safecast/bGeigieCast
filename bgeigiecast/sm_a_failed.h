#ifndef BGEIGIECAST_SM_A_FAILED_H
#define BGEIGIECAST_SM_A_FAILED_H

#include "sm_a_state.h"

class ApiReportFailedState : public ApiReporterState {
 public:
  explicit ApiReportFailedState(IApiConnector& context, Reading* reading);
  virtual ~ApiReportFailedState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_A_FAILED_H

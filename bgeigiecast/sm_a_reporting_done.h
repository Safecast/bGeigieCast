#ifndef BGEIGIECAST_SM_A_REPORTING_DONE_H
#define BGEIGIECAST_SM_A_REPORTING_DONE_H

#include "sm_a_state.h"

class ApiReportDoneState : public ApiReporterState {
 public:
  explicit ApiReportDoneState(IApiConnector& context, IApiConnector::ReportApiStatus status);
  virtual ~ApiReportDoneState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:
  IApiConnector::ReportApiStatus status;
};

#endif //BGEIGIECAST_SM_A_REPORTING_DONE_H

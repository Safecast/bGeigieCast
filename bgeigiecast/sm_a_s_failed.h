#ifndef BGEIGIECAST_SM_A_S_FAILED_H
#define BGEIGIECAST_SM_A_S_FAILED_H

#include "sm_a_failed.h"

class ApiReportSavedFailedState : public ApiReportFailedState {
 public:
  explicit ApiReportSavedFailedState(IApiConnector& context, Reading* reading);
  virtual ~ApiReportSavedFailedState() = default;

  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_A_S_FAILED_H

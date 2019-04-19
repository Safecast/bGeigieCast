#ifndef BGEIGIECAST_SM_A_PROCESS_H
#define BGEIGIECAST_SM_A_PROCESS_H

#include "sm_a_state.h"

class ApiProcessReadingState : public ApiReporterState {
 public:
  explicit ApiProcessReadingState(IApiConnector& context, Reading* reading);
  virtual ~ApiProcessReadingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};


#endif //BGEIGIECAST_SM_A_PROCESS_H

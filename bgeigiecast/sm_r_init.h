#ifndef BGEIGIECAST_SM_R_INIT_H
#define BGEIGIECAST_SM_R_INIT_H

#include "sm_r_state.h"

class InitReporterState : public ReporterState {
 public:
  explicit InitReporterState(Reporter& context);
  virtual ~InitReporterState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_R_INIT_H

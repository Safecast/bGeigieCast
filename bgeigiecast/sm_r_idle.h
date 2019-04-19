#ifndef BGEIGIECAST_SM_R_IDLE_HPP
#define BGEIGIECAST_SM_R_IDLE_HPP

#include "sm_r_state.h"

class ReporterIdleState : public ReporterState {
 public:
  explicit ReporterIdleState(Reporter& context);
  virtual ~ReporterIdleState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_R_IDLE_HPP

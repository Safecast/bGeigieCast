#ifndef BGEIGIECAST_SM_R_GET_READING_H
#define BGEIGIECAST_SM_R_GET_READING_H

#include "sm_r_state.h"

class GetReadingState : public ReporterState {
 public:
  explicit GetReadingState(Reporter& context);
  virtual ~GetReadingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};
#endif //BGEIGIECAST_SM_R_GET_READING_H

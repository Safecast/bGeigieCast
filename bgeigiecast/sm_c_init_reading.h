#ifndef BGEIGIECAST_SM_C_INIT_READING_H
#define BGEIGIECAST_SM_C_INIT_READING_H

#include "sm_c_state.h"


class InitReadingState : public ControllerState {
 public:
  explicit InitReadingState(Controller& context);
  virtual ~InitReadingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_C_INIT_READING_H

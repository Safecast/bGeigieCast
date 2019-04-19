#ifndef BGEIGIECAST_INITIALIZESTATE_H
#define BGEIGIECAST_INITIALIZESTATE_H

#include "sm_c_state.h"

class InitializeState: public ControllerState {
 public:
  explicit InitializeState(Controller& context);
  virtual ~InitializeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:

};

#endif //BGEIGIECAST_INITIALIZESTATE_H

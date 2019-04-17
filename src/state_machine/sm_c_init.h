#ifndef BGEIGIE_POINTCAST_INITIALIZESTATE_H
#define BGEIGIE_POINTCAST_INITIALIZESTATE_H

#include "sm_c_state.h"

class InitializeState__: public State {
 public:
  InitializeState__(Controller& context);
  virtual ~InitializeState__() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:

};

#endif //BGEIGIE_POINTCAST_INITIALIZESTATE_H

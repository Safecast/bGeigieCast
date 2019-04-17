#ifndef BGEIGIE_POINTCAST_POSTINITIALIZESTATE_H
#define BGEIGIE_POINTCAST_POSTINITIALIZESTATE_H

#include "sm_c_state.h"

class PostInitializeState__: public State {
 public:
  PostInitializeState__(Controller& context);
  virtual ~PostInitializeState__() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:

  uint32_t timer;
};

#endif //BGEIGIE_POINTCAST_POSTINITIALIZESTATE_H

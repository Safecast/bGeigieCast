#ifndef BGEIGIE_POINTCAST_POSTINITIALIZESTATE_H
#define BGEIGIE_POINTCAST_POSTINITIALIZESTATE_H

#include "state.h"

class PostInitializeState: public State {
 public:
  PostInitializeState(Controller& context);
  virtual ~PostInitializeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:

  uint32_t timer;
};

#endif //BGEIGIE_POINTCAST_POSTINITIALIZESTATE_H

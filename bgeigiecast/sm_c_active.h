#ifndef BGEIGIECAST_ACTIVESTATE_HPP
#define BGEIGIECAST_ACTIVESTATE_HPP

#include "sm_c_state.h"

class ActiveState: public ControllerState {
 public:
  explicit ActiveState(Controller& context);
  virtual ~ActiveState() = default;

  void do_activity() override;

  void handle_event(Event_enum event_id) override;
};

#endif //BGEIGIECAST_ACTIVESTATE_HPP

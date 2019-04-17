#ifndef BGEIGIE_POINTCAST_ACTIVESTATE_HPP
#define BGEIGIE_POINTCAST_ACTIVESTATE_HPP

#include "sm_c_state.h"

class ActiveState__: public State {
 public:
  ActiveState__(Controller& context);
  virtual ~ActiveState__() = default;
  void handle_event(Event_enum event_id) override;
};

#endif //BGEIGIE_POINTCAST_ACTIVESTATE_HPP

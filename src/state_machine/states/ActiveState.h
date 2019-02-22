#ifndef BGEIGIE_POINTCAST_ACTIVESTATE_HPP
#define BGEIGIE_POINTCAST_ACTIVESTATE_HPP

#include "state.h"

class ActiveState: public State {
 public:
  ActiveState(Controller& context);
  virtual ~ActiveState() = default;

};

#endif //BGEIGIE_POINTCAST_ACTIVESTATE_HPP

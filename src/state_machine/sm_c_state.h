#ifndef BGEIGIE_POINTCAST_STATE_HPP
#define BGEIGIE_POINTCAST_STATE_HPP

#include "../debugger.h"
#include "../controller.h"


/**
 * State with controller context, so the states can control the system
 */
class ControllerState: public State {
 public:
  explicit ControllerState(Controller& context): controller(context){};
  virtual ~ControllerState() = default;
 protected:
  Controller& controller;
};

#endif //BGEIGIE_POINTCAST_STATE_HPP
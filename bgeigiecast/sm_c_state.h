#ifndef BGEIGIECAST_STATE_HPP
#define BGEIGIECAST_STATE_HPP

#include "debugger.h"
#include "controller.h"
#include "sm_state.h"

/**
 * BaseState with controller context, so the states can control the system
 */
class ControllerState : public BaseState {
 public:

  explicit ControllerState(Controller& context) : controller(context) {};
  virtual ~ControllerState() = default;

 protected:
  Controller& controller;
};

#endif //BGEIGIECAST_STATE_HPP

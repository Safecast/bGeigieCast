#ifndef BGEIGIECAST_STATE_HPP
#define BGEIGIECAST_STATE_HPP

#include "debugger.h"
#include "controller.h"
#include "sm_state.h"

/**
 * State with controller context, so the states can control the system
 */
class ControllerState : public State {
 public:
  enum StateId {
    k_state_InitializeState,
    k_state_InitReadingState,
    k_state_PostInitializeState,
    k_state_ConfigurationModeState,
    k_state_MobileModeState,
    k_state_FixedModeState,
    k_state_ResetState,
  };

  explicit ControllerState(Controller& context) : controller(context) {};
  virtual ~ControllerState() = default;

 protected:
  Controller& controller;
};

#endif //BGEIGIECAST_STATE_HPP

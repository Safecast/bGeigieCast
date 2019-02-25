#ifndef BGEIGIE_POINTCAST_STATE_HPP
#define BGEIGIE_POINTCAST_STATE_HPP

#include <debugger.h>
#include "controller.h"

typedef enum {
  e_initializing,
  e_setup_server,
  e_server_active,
  e_active,
  e_active_mobile_mode,
  e_active_stationary_mode,
  e_active_stationary_mode_connecting,
  e_active_stationary_mode_connection_test,
  e_active_stationary_mode_connected,
  e_active_stationary_mode_reconnecting,
} State_enum;

/**
 * State with controller context, so the states can control the system
 */
class State: public AbstractState {
 public:
  State(Controller& context): controller(context){};
  virtual ~State() = default;

  void handle_event(Event_enum event_id) override {
    debug_print("State machine: Unhandled event with id: ");
    debug_println(event_id);
  }
 protected:
  Controller& controller;
};

#endif //BGEIGIE_POINTCAST_STATE_HPP

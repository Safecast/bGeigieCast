#ifndef BGEIGIE_POINTCAST_STATE_HPP
#define BGEIGIE_POINTCAST_STATE_HPP

#include <debugger.h>
#include "controller.h"


/**
 * State with controller context, so the states can control the system
 */
class State: public AbstractState__ {
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

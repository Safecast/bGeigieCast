#ifndef BGEIGIECAST_ABSTRACT_STATE_HPP
#define BGEIGIECAST_ABSTRACT_STATE_HPP

#include "sm_events.h"
#include "debugger.h"

/**
 * Abstract state for the state machine pattern
 */
class State {
 public:
  State() = default;;
  virtual ~State() = default;

  /**
   * Get some unique identifier of the state
   * @return
   */
  virtual int8_t get_state_id() const = 0;

  /**
   * Action when entering this state
   */
  virtual void entry_action() = 0;

  /**
   * Activity while in this state, will be called constantly through the main loop
   */
  virtual void do_activity() = 0;

  /**
   * Action when exiting the state
   */
  virtual void exit_action() = 0;

  /**
   * Handle event
   * @param event_id
   */
  virtual void handle_event(Event_enum event_id) {
    DEBUG_PRINT("State machine: Unhandled event with id: ");
    DEBUG_PRINTLN(event_id);
  }
};

#endif //BGEIGIECAST_STATE_HPP

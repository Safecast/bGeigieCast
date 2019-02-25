#ifndef BGEIGIE_POINTCAST_ABSTRACT_STATE_HPP
#define BGEIGIE_POINTCAST_ABSTRACT_STATE_HPP

#include "events.h"

/**
 * Abstract state for the state machine pattern
 */
class AbstractState {
 public:
  AbstractState(){};
  virtual ~AbstractState() = default;

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
  virtual void handle_event(Event_enum event_id) = 0;
};


#endif //BGEIGIE_POINTCAST_STATE_HPP

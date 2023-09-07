#ifndef BGEIGIECAST_CONTEXT_H
#define BGEIGIECAST_CONTEXT_H

#define MAX_EVENTS 10

#include "sm_state.h"
#include "circular_buffer.h"

/**
 * Context, something which will control a set of states and runs a state machine
 */
class Context {
 public:
  Context();
  virtual ~Context();

  /**
   * Will exit the current one and enter the new one
   * @param state: New state to be set
   */
  virtual void set_state(BaseState* state);

  virtual /**
   * Run the state machine once, will handle scheduled events and run the do activity from the state
   */
  void run();

  /**
   * Schedule a new event
   * @param event_id
   */
  void schedule_event(Event_enum event_id);

  /**
   * Get current state
   * @return
   */
  BaseState* get_current_state() const;

  /**
   * Clear all events in the event queue
   */
  void clear_events();

  /**
   * Handle all events in queue for current state
   */
  void handle_events();
 private:

  BaseState* _current_state;
  CircularBuffer<Event_enum, MAX_EVENTS> _event_queue;
};

#endif //BGEIGIECAST_CONTEXT_H

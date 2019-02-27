#ifndef BGEIGIE_POINTCAST_CONTEXT_H
#define BGEIGIE_POINTCAST_CONTEXT_H

#define MAX_EVENTS 10

#include "abstract_state.h"
#include <circular_buffer.h>


/**
 * Context, will be inherited by the controller so it can run the state machine
 */
class Context {
 public:
  Context();
  virtual ~Context();

  /**
   * Will exit the current one and enter the new one
   * @param state: New state to be set
   */
  void set_state(AbstractState* state);

  /**
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
  AbstractState* get_current_state() const;

  /**
   * Clear all events in the event queue
   */
  void clear_events();

  /**
   * Handle all events in queue for current state
   */
  void handle_events();
 private:

  AbstractState* current_state;
  CircularBuffer<Event_enum, MAX_EVENTS, Event_enum::e_undefined> eventQueue;
};

#endif //BGEIGIE_POINTCAST_CONTEXT_H

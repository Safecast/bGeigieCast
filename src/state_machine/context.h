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
  virtual ~Context() = default;

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
  void schedue_event(Event_enum event_id);
 private:

  AbstractState* currentState;
  CircularBuffer<Event_enum, MAX_EVENTS> eventQueue;
};

#endif //BGEIGIE_POINTCAST_CONTEXT_H

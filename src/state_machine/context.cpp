#include <debugger.h>
#include "context.h"

Context::Context() : currentState(nullptr), eventQueue() {
}

void Context::set_state(AbstractState* state) {
  if(currentState) {
    currentState->exit_action();
    delete currentState;
  }
  currentState = state;
  currentState->entry_action();
  currentState->do_activity();
}

void Context::run() {
  if(!currentState) {
    debug_println("Trying to run state machine with no active state");
    return;
  }
  while(!eventQueue.empty()) {
    Event_enum event_id = eventQueue.get();
    currentState->handle_event(event_id);
  }
  currentState->do_activity();
}

void Context::schedule_event(Event_enum event_id) {
  eventQueue.add(event_id);
}



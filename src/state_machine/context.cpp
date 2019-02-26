#include <debugger.h>
#include "context.h"

Context::Context() : current_state(nullptr), eventQueue() {
}

void Context::set_state(AbstractState* state) {
  if(current_state) {
    current_state->exit_action();
    delete current_state;
  }
  current_state = state;
  current_state->entry_action();
  current_state->do_activity();
}

void Context::run() {
  if(!current_state) {
    debug_println("Trying to run state machine with no active state");
    return;
  }
  while(!eventQueue.empty()) {
    Event_enum event_id = eventQueue.get();
    current_state->handle_event(event_id);
  }
  current_state->do_activity();
}

void Context::schedule_event(Event_enum event_id) {
  eventQueue.add(event_id);
}

AbstractState* Context::get_current_state() const {
  return current_state;
}

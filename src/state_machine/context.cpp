#include <debugger.h>
#include "context.h"

Context::Context() : current_state(nullptr), eventQueue() {
}

Context::~Context() {
  if(current_state) {
    current_state->exit_action();
    delete current_state;
  }
}

void Context::set_state(AbstractState* state) {
  if(current_state) {
    current_state->exit_action();
    delete current_state;
  }
  current_state = state;
  current_state->entry_action();
}

void Context::run() {
  if(!current_state) {
    debug_println("Trying to run state machine with no active state");
    return;
  }
  current_state->do_activity();
  handle_events();
}

void Context::schedule_event(Event_enum event_id) {
  eventQueue.add(event_id);
}

AbstractState* Context::get_current_state() const {
  return current_state;
}

void Context::clear_events() {
  eventQueue.clear();
}

void Context::handle_events() {
  while(!eventQueue.empty()) {
    Event_enum event_id = eventQueue.get();
    if(current_state) { current_state->handle_event(event_id); }
  }
}

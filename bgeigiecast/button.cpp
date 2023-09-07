#include "button.h"
#include "debugger.h"

void buttonTrigger(void* arg) {
  if(!arg) {
    return;
  }
  Button* b = ((Button*) arg);
  // Read the pin value here so we can use the state_changed in unit tests
  b->state_changed(digitalRead(b->get_pin()), millis());
}

Button::Button(uint8_t pin, uint8_t pull_type) :
    Worker<ButtonTrigger>(),
    _pin(pin),
    _changed(false),
    _pull_type_mode(pull_type == PULLDOWN ? HIGH : LOW),
    _current_state(false),
    _last_state_change(0) {
}

Button::~Button() {
  gpio_isr_handler_remove((gpio_num_t) _pin);
}

bool Button::activate(bool retry) {
  gpio_set_intr_type((gpio_num_t) _pin, GPIO_INTR_ANYEDGE);
  gpio_isr_handler_add((gpio_num_t) _pin, buttonTrigger, this);
  _current_state = digitalRead(_pin) == _pull_type_mode;
  return true;
}

bool Button::currently_pressed() const {
  return _current_state;
}

bool Button::state_changed(int state, uint32_t time) {
  bool new_state = state == _pull_type_mode;
  if(new_state == _current_state || _last_state_change + BUTTON_DEBOUNCE_TIME_MILLIS > time) {
    _current_state = new_state;
    return false;
  }
  _current_state = new_state;
  _changed = true;

  if(_current_state) {
    data.state = ButtonTrigger::DOWN;
    data.pressDuration = 0;
  } else if(_last_state_change != 0) { // Ignore initial presses at startups
    data.state = ButtonTrigger::UP;
    data.pressDuration = time - _last_state_change;
  }
  _last_state_change = time;
  return true;
}

uint8_t Button::get_pin() const {
  return _pin;
}

uint32_t Button::get_last_state_change() const {
  return _last_state_change;
}

int8_t Button::produce_data() {
  if(_changed) {
    _changed = false;
    return e_worker_data_read;
  }
  return e_worker_idle;
}

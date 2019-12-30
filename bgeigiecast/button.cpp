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
    _pin(pin),
    _pull_type_mode(pull_type == PULLDOWN ? HIGH : LOW),
    _observer(nullptr),
    _current_state(false),
    _last_state_change(0) {
}

Button::~Button() {
  gpio_isr_handler_remove((gpio_num_t) _pin);
}

void Button::activate() {
  gpio_set_intr_type((gpio_num_t) _pin, GPIO_INTR_ANYEDGE);
  gpio_isr_handler_add((gpio_num_t) _pin, buttonTrigger, this);
  _current_state = digitalRead(_pin) == _pull_type_mode;
}

void Button::set_observer(ButtonObserver* observer) {
  _observer = observer;
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

  if(_current_state) {
    if(_observer) { _observer->on_button_down(this); }
  } else if(_last_state_change != 0) { // Ignore initial presses at startups
    if(_observer) { _observer->on_button_release(this); }
    if(_observer) { _observer->on_button_pressed(this, time - _last_state_change); }
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

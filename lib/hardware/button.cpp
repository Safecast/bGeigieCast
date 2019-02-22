#include "button.h"

void buttonTrigger(void* arg) {
  if(!arg) {
    return;
  }
  ((Button*) arg)->stateChanged();
}

Button::Button(uint8_t pin, uint8_t pull_type) :
    _pin(pin),
    _pull_type_mode(pull_type == PULLDOWN ? LOW : HIGH),
    _observer(nullptr),
    _current_state(false),
    _last_state_change(0) {
  pinMode(pin, INPUT);
  attachInterruptArg(pin, buttonTrigger, this, CHANGE);
}

void Button::set_observer(ButtonObserver* observer) {
  _observer = observer;
}

bool Button::currently_pressed() const {
  return _current_state || digitalRead(_pin);
}

void Button::stateChanged() {
  bool read_state = digitalRead(_pin) == _pull_type_mode;
  if(!_observer || _last_state_change + DEBOUNCE_TIME_MILLIS > millis() || read_state == _current_state) {
    return;
  }
  uint32_t time = millis();
  _current_state = read_state;

  if(_current_state) {
    _observer->on_button_down(this);
  }
  else {
    _observer->on_button_release(this);
    _observer->on_button_pressed(this, time - _last_state_change);
  }
  _last_state_change = time;
}

uint8_t Button::get_pin() const {
  return _pin;
}



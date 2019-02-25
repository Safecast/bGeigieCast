#include "button.h"

void IRAM_ATTR buttonTrigger(void* arg) {
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
    _last_state_change(0),
    _on_button_down_fn(nullptr),
    _on_button_release_fn(nullptr),
    _on_button_pressed_fn(nullptr) {
  pinMode(pin, INPUT);
  attachInterruptArg(pin, buttonTrigger, this, CHANGE);
  _current_state = digitalRead(_pin) == _pull_type_mode;
}

void Button::set_observer(ButtonObserver* observer) {
  _observer = observer;
}

bool Button::currently_pressed() const {
  return _current_state;
}

void Button::stateChanged() {
  bool read_state = digitalRead(_pin) == _pull_type_mode;
  if(_last_state_change + DEBOUNCE_TIME_MILLIS > millis() || read_state == _current_state) {
    return;
  }
  uint32_t time = millis();
  _current_state = read_state;

  if(_current_state) {
    if(_observer) { _observer->on_button_down(this); }
    if(_on_button_down_fn) { _on_button_down_fn(this); }
  } else if(_last_state_change != 0) { // Ignore initial presses at startups
    if(_observer) { _observer->on_button_release(this); }
    if(_on_button_release_fn) { _on_button_release_fn(this); }
    if(_observer) { _observer->on_button_pressed(this, time - _last_state_change); }
    if(_on_button_pressed_fn) { _on_button_pressed_fn(this, time - _last_state_change); }
  }
  _last_state_change = time;
}

uint8_t Button::get_pin() const {
  return _pin;
}

void Button::set_on_button_down_fn(on_button_down_fn_t on_button_down_fn) {
  _on_button_down_fn = on_button_down_fn;
}

void Button::set_on_button_release_fn(on_button_release_fn_t on_button_release_fn) {
  _on_button_release_fn = on_button_release_fn;
}

void Button::set_on_button_pressed_fn(on_button_pressed_fn_t on_button_pressed_fn) {
  _on_button_pressed_fn = on_button_pressed_fn;
}


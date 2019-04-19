#include "button.h"

volatile uint32_t temp = 0;

void buttonTrigger(void* arg) {
  if(!arg) {
    return;
  }
  Button* b = ((Button*) arg);
  // Read the pin value here so we can use the state_changed in unit tests
  b->state_changed(digitalRead(b->get_pin()));
}

Button::Button(uint8_t pin, uint8_t pull_type) :
    _pin(pin),
    _pull_type_mode(pull_type == PULLDOWN ? HIGH : LOW),
    _observer(nullptr),
    _current_state(digitalRead(_pin) == _pull_type_mode),
    _last_state_change(0),
    _on_button_down_fn(nullptr),
    _on_button_release_fn(nullptr),
    _on_button_pressed_fn(nullptr) {
}

Button::~Button() {
  gpio_reset_pin((gpio_num_t) _pin);
  gpio_isr_handler_remove((gpio_num_t) _pin);
}

void Button::activate() {
  gpio_set_intr_type((gpio_num_t) _pin, GPIO_INTR_ANYEDGE);
  gpio_isr_handler_add((gpio_num_t) _pin, buttonTrigger, this);
}

void Button::set_observer(ButtonObserver* observer) {
  _observer = observer;
}

bool Button::currently_pressed() const {
  return _current_state;
}

bool Button::state_changed(int state) {
  _current_state = state == _pull_type_mode;
  if(_last_state_change + DEBOUNCE_TIME_MILLIS > millis()) {
    return false;
  }

  uint32_t time = (uint32_t) (esp_timer_get_time() / 1000);

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
  return true;
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


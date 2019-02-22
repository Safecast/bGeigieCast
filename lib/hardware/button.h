#ifndef BGEIGIE_POINTCAST_BUTTON_HPP
#define BGEIGIE_POINTCAST_BUTTON_HPP

#define DEBOUNCE_TIME_MILLIS 50


#include <Arduino.h>
#include "button_observer.h"

/**
 * A nice button class
 */
class Button {
 public:
  Button(uint8_t pin, uint8_t pull_type = PULLUP);
  virtual ~Button() = default;

  /**
   * Let the button know that the state has changed
   */
  void stateChanged();

  /**
   * Set an observer for this button
   * @param observer
   */
  void set_observer(ButtonObserver* observer);
  uint8_t get_pin() const;
  /**
   * check if the button is currently hold down
   * @return: true if button is down
   */
  bool currently_pressed() const;

 private:
  uint8_t _pin;
  bool _pull_type_mode;
  ButtonObserver* _observer;
  bool _current_state;
  uint32_t _last_state_change;
};


#endif //BGEIGIE_POINTCAST_BUTTON_HPP

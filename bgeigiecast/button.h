#ifndef BGEIGIECAST_BUTTON_HPP
#define BGEIGIECAST_BUTTON_HPP

#define DEBOUNCE_TIME_MILLIS 50


#include <Arduino.h>
#include "button_observer.h"

/**
 * A nice button class
 */
class Button {
 public:

  typedef void(*on_button_down_fn_t)(Button*);
  typedef void(*on_button_release_fn_t)(Button*);
  typedef void(*on_button_pressed_fn_t)(Button*, uint32_t);


  Button(uint8_t pin, uint8_t pull_type = PULLUP);
  virtual ~Button();

  /**
   * Installs the button in the interrupt service
   */
  void activate();

  /**
   * Let the button know that the state has changed
   * @param state: LOW / HIGH reading from the button
   * @param time: current time
   * @return: true if event was handled (false if ignored)
   */
  bool state_changed(int state, uint32_t time);

  /**
   * Get pin number
   * @return: pin number
   */
  uint8_t get_pin() const;

  /**
   * check if the button is currently hold down
   * @return: true if button is down
   */
  bool currently_pressed() const;

  /**
   * Set an observer for this button (for callback to class methods)
   * @param observer
   */
  void set_observer(ButtonObserver* observer);

  /**
   * Set a callback function for button down events
   * @param on_button_down_fn: callback function
   */
  void set_on_button_down_fn(on_button_down_fn_t on_button_down_fn);

  /**
   * Set a callback function for button release events
   * @param on_button_down_fn: callback function
   */
  void set_on_button_release_fn(on_button_release_fn_t on_button_release_fn);

  /**
   * Set a callback function for button pressed events
   * @param on_button_down_fn: callback function
   */
  void set_on_button_pressed_fn(on_button_pressed_fn_t on_button_pressed_fn);
 private:
  uint8_t _pin;
  bool _pull_type_mode;
  ButtonObserver* _observer;
  bool _current_state;
  uint32_t _last_state_change;

  on_button_down_fn_t _on_button_down_fn;
  on_button_release_fn_t _on_button_release_fn;
  on_button_pressed_fn_t _on_button_pressed_fn;
};


#endif //BGEIGIECAST_BUTTON_HPP

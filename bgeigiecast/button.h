#ifndef BGEIGIECAST_BUTTON_HPP
#define BGEIGIECAST_BUTTON_HPP

#define BUTTON_DEBOUNCE_TIME_MILLIS 50

#include <Arduino.h>

class ButtonObserver;

/**
 * A nice button class
 */
class Button {
 public:

  explicit Button(uint8_t pin, uint8_t pull_type = PULLUP);
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
   * Get the moment last state changed (getter)
   * @return millis of last change
   */
  uint32_t get_last_state_change() const;

  /**
   * Set an observer for this button (for callback to class methods)
   * @param observer
   */
  void set_observer(ButtonObserver* observer);

 private:
  uint8_t _pin;
  bool _pull_type_mode;
  ButtonObserver* _observer;
  bool _current_state;
  uint32_t _last_state_change;
};

/**
 * Anything can be an observer of a button... This class is used to let the button know who observes it.
 */
class ButtonObserver {
 public:
  ButtonObserver() = default;
  virtual ~ButtonObserver() = default;

  /**
   * Callback when the button is pressed down
   * if button is PULLUP, triggers when HIGH -> LOW
   * if button is PULLDOWN, triggers when  LOW -> HIGH
   * @param button: The button that caused the trigger
   */
  virtual void on_button_down(Button* button) {/*no implementation*/};

  /**
   * Callback when the button is released
   * if button is PULLUP, triggers when LOW -> HIGH
   * if button is PULLDOWN, triggers when HIGH -> LOW
   * @param button: The button that caused the trigger
   */
  virtual void on_button_release(Button* button) {/*no implementation*/};

  /**
   *
   * Callback when the button was pressed (down + release)
   * if button is PULLUP, triggers when HIGH -> LOW -> HIGH
   * if button is PULLDOWN, triggers when  LOW -> HIGH -> LOW
   * @param button: The button that caused the trigger
   * @param millis: how long the button was pressed in millis
   */
  virtual void on_button_pressed(Button* button, uint32_t millis) {/*no implementation*/};
};

#endif //BGEIGIECAST_BUTTON_HPP

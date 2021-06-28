#ifndef BGEIGIECAST_BUTTON_HPP
#define BGEIGIECAST_BUTTON_HPP

#define BUTTON_DEBOUNCE_TIME_MILLIS 50

#include <Arduino.h>
#include <Worker.hpp>

class ButtonObserver;

struct ButtonTrigger {
  enum ButtonStatus {
    DOWN,
    UP
  };

  ButtonStatus state;
  uint16_t pressDuration;
};

/**
 * A nice button class
 */
class Button : public Worker<ButtonTrigger> {
 public:

  explicit Button(uint8_t pin, uint8_t pull_type = PULLUP);
  virtual ~Button();

  /**
   * Installs the button in the interrupt service
   */
  bool activate(bool retry) override;

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

  int8_t produce_data() override;

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

 private:
  uint8_t _pin;
  bool _changed;
  bool _pull_type_mode;
  bool _current_state;
  uint32_t _last_state_change;
};

#endif //BGEIGIECAST_BUTTON_HPP

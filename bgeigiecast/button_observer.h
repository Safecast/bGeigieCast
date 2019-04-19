#ifndef BGEIGIECAST_BUTTONOBSERVER_H
#define BGEIGIECAST_BUTTONOBSERVER_H

class Button;

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

#endif //BGEIGIECAST_BUTTONOBSERVER_H

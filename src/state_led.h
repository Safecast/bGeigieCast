#ifndef BGEIGIE_POINTCAST_STATE_LED_H
#define BGEIGIE_POINTCAST_STATE_LED_H

#include <rgb_led.h>

/**
 * Controls the LED to visualize the current state
 */
class StateLED : private RGBLed{
 public:
  typedef enum {
    off,
    init,
    config,
    mobile,
    stationary_connecting,
    stationary_active,
    stationary_error
  } StateColor;
  StateLED();
  virtual ~StateLED() = default;

  void set_color(StateColor color);

  void blink(StateColor color, uint32_t frequency);

 private:
  bool blink_state;
  RGB _rgb_off;
  RGB _rgb_init;
  RGB _rgb_config;
  RGB _rgb_mobile;
  RGB _rgb_stationary_connecting;
  RGB _rgb_stationary_active;
  RGB _rgb_stationary_error;
};

#endif //BGEIGIE_POINTCAST_STATE_LED_H

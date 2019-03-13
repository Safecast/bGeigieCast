#include "state_led.h"
#include "user_config.h"
#include "debugger.h"

// Set this to true if we use anode LED
#define RGB_STATE_LED_REVERSED false

StateLED::StateLED() :
    RGBLed(RGB_LED_PIN_R, RGB_LED_PIN_G, RGB_LED_PIN_B, RGB_STATE_LED_REVERSED),
    blink_state(false),
    _rgb_off{0, 0, 0},
    _rgb_init{50, 50, 50},
    _rgb_config{255, 0, 255},
    _rgb_mobile{0, 0, 255},
    _rgb_stationary_connecting{0, 255, 0},
    _rgb_stationary_active{0, 255, 0},
    _rgb_stationary_error{255, 0, 0} {
}

void StateLED::set_state_led(StateLED::StateColor color) {
  debug_print("Changed LED to "); debug_println(color);
  switch(color) {
    case off:
      set(_rgb_off);
      break;
    case init:
      set(_rgb_init);
      break;
    case config:
      set(_rgb_config);
      break;
    case mobile:
      set(_rgb_mobile);
      break;
    case stationary_connecting:
      set(_rgb_stationary_connecting);
      break;
    case stationary_active:
      set(_rgb_stationary_active);
      break;
    case stationary_error:
      set(_rgb_stationary_error);
      break;
  }
}
void StateLED::blink(StateLED::StateColor color, uint32_t frequency) {
  // Blink LED
  if(millis() % frequency > frequency / 2 && !blink_state) {
    set_state_led(color);
    blink_state = true;
  } else if(millis() % frequency < frequency / 2 && blink_state){
    set_state_led(StateLED::StateColor::off);
    blink_state = false;
  }
}

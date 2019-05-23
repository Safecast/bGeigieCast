
#include "mode_led.h"
#include "user_config.h"
#include "debugger.h"

// Set this to true if we use anode LED
#define RGB_STATE_LED_REVERSED true

ModeLED::ModeLED(IEspConfig& config) :
    RGBLed(RGB_LED_PIN_R, RGB_LED_PIN_G, RGB_LED_PIN_B, RGB_STATE_LED_REVERSED),
    _config(config),
    _blink_state(false),
    _colorTypes{
        // Normal           Colorblind
        // R    G    B      R    G    B
        {{000, 000, 000}, {000, 000, 000}}, // off
        {{063, 127, 063}, {063, 127, 063}}, // init
        {{063, 000, 063}, {063, 000, 063}}, // init config
        {{127, 000, 127}, {127, 000, 127}}, // config
        {{000, 127, 255}, {000, 127, 255}}, // mobile
        {{127, 255, 000}, {127, 255, 000}}, // fixed_connecting
        {{000, 255, 000}, {000, 255, 127}}, // fixed_active
        {{255, 000, 000}, {255, 127, 000}}, // fixed_error
    } {
}

void ModeLED::set_color(ModeLED::ModeColor color) {
  DEBUG_PRINT("Changed LED to ");
  DEBUG_PRINTLN(color);
  set(_config.is_led_color_blind() ? _colorTypes[color].color_blind : _colorTypes[color].normal);
}

void ModeLED::blink(ModeLED::ModeColor color, double frequency, double percentage_on) {
  // Blink LED
  double blink_millis = 1000/frequency;
  uint32_t cycle_now = millis() % static_cast<uint32_t>(blink_millis);
  uint32_t threshold = static_cast<uint32_t>(blink_millis * (percentage_on / 100));
  if(cycle_now < threshold && !_blink_state) {
    set_color(color);
    _blink_state = true;
  } else if(cycle_now > threshold && _blink_state) {
    set_color(ModeLED::ModeColor::off);
    _blink_state = false;
  }
}

uint8_t ModeLED::get_intensity() const {
  return _config.get_led_color_intensity();
}

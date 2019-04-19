
#include "state_led.h"
#include "user_config.h"
#include "debugger.h"

// Set this to true if we use anode LED
#define RGB_STATE_LED_REVERSED true

StateLED::StateLED(IEspConfig& config) :
    RGBLed(RGB_LED_PIN_R, RGB_LED_PIN_G, RGB_LED_PIN_B, RGB_STATE_LED_REVERSED),
    _config(config),
    _blink_state(false),
    _colorTypes{
        {{000, 000, 000}, {000, 000, 000}},
        {{128, 064, 128}, {050, 050, 050}},
        {{255, 000, 255}, {000, 000, 255}},
        {{000, 000, 255}, {000, 255, 255}},
        {{128, 128, 000}, {255, 255, 000}},
        {{000, 255, 000}, {000, 000, 255}},
        {{255, 000, 000}, {255, 000, 255}},
    } {
}

void StateLED::set_color(StateLED::StateColor color) {
  DEBUG_PRINT("Changed LED to ");
  DEBUG_PRINTLN(color);
  set(_config.is_led_color_blind() ? _colorTypes[color].color_blind : _colorTypes[color].normal);
}
void StateLED::blink(StateLED::StateColor color, uint32_t frequency) {
  // Blink LED
  if(millis() % frequency > frequency / 2 && !_blink_state) {
    set_color(color);
    _blink_state = true;
  } else if(millis() % frequency < frequency / 2 && _blink_state) {
    set_color(StateLED::StateColor::off);
    _blink_state = false;
  }
}

uint8_t StateLED::get_intensity() const {
  return _config.get_led_color_intensity();
}

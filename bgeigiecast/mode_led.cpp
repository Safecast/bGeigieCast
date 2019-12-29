
#include "mode_led.h"
#include "user_config.h"
#include "debugger.h"

// Set this to true if we use anode LED
#define RGB_STATE_LED_REVERSED true

ModeLED::ModeLED(LocalStorage& config) :
    RGBLed(RGB_LED_PIN_R, RGB_LED_PIN_G, RGB_LED_PIN_B, RGB_STATE_LED_REVERSED),
    Supervisor(),
    _config(config),
    color(ModeColor::mode_color_off),
    frequency(0),
    percentage_on(0),
    _colorTypes{
        // Normal            Colorblind
        // R    G    B   ,   R    G    B
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

void ModeLED::set_color(ModeLED::ModeColor _color, double _frequency, uint8_t _percentage_on) {
  DEBUG_PRINT("Changed LED to ");
  DEBUG_PRINTLN(_color);
  color = _color;
  if (frequency > 0){
    frequency = _frequency;
    percentage_on = _percentage_on;
  }
  else {
    // If not blinking, set here. Else the loop will take care of the setter
    set(_config.is_led_color_blind() ? _colorTypes[color].color_blind : _colorTypes[color].normal);
  }
}

void ModeLED::loop() {
  if(frequency > 0) {
    // Blink LED
    double blink_millis = 1000 / frequency;
    auto cycle_now = millis() % static_cast<uint32_t>(blink_millis);
    auto threshold = static_cast<uint32_t>(blink_millis * (percentage_on / 100.0));
    if(cycle_now < threshold) {
      set_color(color);
    } else if(cycle_now > threshold) {
      set_color(ModeLED::mode_color_off);
    }
  }
}

uint8_t ModeLED::get_intensity() const {
  return _config.get_led_color_intensity();
}

bool ModeLED::activate() {
  init();
  return true;
}

void ModeLED::handle_report(const Report& report) {
  // TODO
}

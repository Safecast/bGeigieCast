#include "rgb_led.h"

#define CHANNEL_R 0
#define CHANNEL_G 1
#define CHANNEL_B 2

#define CHANNEL_FREQUENCY 12800
#define CHANNEL_RESOLUTION 8

RGBLed::RGBLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, bool reversed) : _reversed(reversed), _intensity(255) {
  // Connect pins to channels
  ledcSetup(CHANNEL_R, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcAttachPin(pin_r, CHANNEL_R);
  ledcSetup(CHANNEL_G, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcAttachPin(pin_g, CHANNEL_G);
  ledcSetup(CHANNEL_B, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcAttachPin(pin_b, CHANNEL_B);
}

void RGBLed::set(const RGB& values) {
  set_r(values.r);
  set_g(values.g);
  set_b(values.b);
}

void RGBLed::off() {
  set_r(0);
  set_g(0);
  set_b(0);
}

void RGBLed::set_intensity(uint8_t intensity) {
  _intensity = intensity;
}

uint8_t RGBLed::get_intensity() const {
  return _intensity > 100 ? 100 : _intensity;
}

void RGBLed::set_r(uint8_t value) {
  set_channel(CHANNEL_R, value);
}

void RGBLed::set_g(uint8_t value) {
  set_channel(CHANNEL_G, value);
}

void RGBLed::set_b(uint8_t value) {
  set_channel(CHANNEL_B, value);
}

void RGBLed::set_channel(uint8_t channel, uint8_t value) {
  uint32_t modified_value = static_cast<int32_t>((static_cast<float>(get_intensity()) / 255) * value);
  // using 256 below because when its inverted 255 will still be very dim, 256 will be 100% turned off.
  ledcWrite(channel, _reversed ? (256 - modified_value) : modified_value);
}
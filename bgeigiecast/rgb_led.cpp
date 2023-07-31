#include "rgb_led.h"
#include "user_config.h"


#ifdef STAMPS3
RGBLed::RGBLed() : config_intensity(30) {
}
#else
RGBLed::RGBLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, bool reversed) : _reversed(reversed), config_intensity(30) {
  ledcAttachPin(pin_r, CHANNEL_R);
  ledcAttachPin(pin_g, CHANNEL_G);
  ledcAttachPin(pin_b, CHANNEL_B);
}
#endif //STAMPS3

void RGBLed::init() {
#ifdef STAMPS3
  FastLED.addLeds<WS2812, FASTLED_PIN, GRB>(leds, NUM_LEDS);
#else
  // Connect pins to channels
  ledcSetup(CHANNEL_R, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcSetup(CHANNEL_G, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcSetup(CHANNEL_B, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
#endif //STAMPS3
  off();
}

void RGBLed::off() {
  set({0, 0, 0});
}

void RGBLed::set_intensity(uint8_t intensity) {
  config_intensity = intensity;
}

uint8_t RGBLed::get_intensity() const {
  return config_intensity;
}

#ifdef STAMPS3
void RGBLed::set(const RGB_e& values) {
  leds[0].setRGB(
      static_cast<int32_t>((get_intensity() / 255.0) * values.r),
      static_cast<int32_t>((get_intensity() / 255.0) * values.g),
      static_cast<int32_t>((get_intensity() / 255.0) * values.b)
  );
  FastLED.show();
}

#else
void RGBLed::set(const RGB_e& values) {
  set_r(values.r);
  set_g(values.g);
  set_b(values.b);
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
  uint32_t modified_value = static_cast<int32_t>((get_intensity() / 255.0) * value);
  // using 256 below because when its inverted 255 will still be very dim, 256 will be 100% turned off.
  ledcWrite(channel, _reversed ? (256 - modified_value) : modified_value);
}

#endif //STAMPS3

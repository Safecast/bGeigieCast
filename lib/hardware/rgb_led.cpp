#include "rgb_led.h"

#define CHANNEL_R 0
#define CHANNEL_G 1
#define CHANNEL_B 2

#define CHANNEL_FREQUENCY 12800
#define CHANNEL_RESOLUTION 8

RGBLed::RGBLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, bool reversed): _reversed(reversed) {
  // Connect pins to channels
  ledcSetup(CHANNEL_R, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcAttachPin(pin_r, CHANNEL_R);
  ledcSetup(CHANNEL_G, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcAttachPin(pin_g, CHANNEL_G);
  ledcSetup(CHANNEL_B, CHANNEL_FREQUENCY, CHANNEL_RESOLUTION);
  ledcAttachPin(pin_b, CHANNEL_B);
}

void RGBLed::set(RGB& values) {
  set_r(values.r);
  set_g(values.g);
  set_b(values.b);
}

void RGBLed::off() {
  set_r(0);
  set_g(0);
  set_b(0);
}

void RGBLed::set_r(uint8_t value){
  ledcWrite(CHANNEL_R, _reversed ? static_cast<uint8_t>(255 - value): value);
}

void RGBLed::set_g(uint8_t value){
  ledcWrite(CHANNEL_G, _reversed ? static_cast<uint8_t>(255 - value) : value);
}

void RGBLed::set_b(uint8_t value){
  ledcWrite(CHANNEL_B, _reversed ? static_cast<uint8_t>(255 - value) : value);
}
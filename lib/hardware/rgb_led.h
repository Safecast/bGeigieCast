#ifndef BGEIGIE_POINTCAST_ESP_LED_H
#define BGEIGIE_POINTCAST_ESP_LED_H

#include <Arduino.h>

typedef struct {
  uint32_t r;
  uint32_t g;
  uint32_t b;
} RGB;

class RGBLed {
 public:
  RGBLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);
  virtual ~RGBLed() = default;

  void set(RGB& values);

  void off();

  void set_r(uint32_t value);
  void set_g(uint32_t value);
  void set_b(uint32_t value);
};

#endif //BGEIGIE_POINTCAST_ESP_LED_H

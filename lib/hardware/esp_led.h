#ifndef BGEIGIE_POINTCAST_ESP_LED_H
#define BGEIGIE_POINTCAST_ESP_LED_H

#include <Arduino.h>

typedef struct {
  uint32_t r;
  uint32_t g;
  uint32_t b;
} RGB;

class EspLED {
 public:
  EspLED(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);
  virtual ~EspLED() = default;

  void set(RGB& values);

  void set_r(uint32_t value);
  void set_g(uint32_t value);
  void set_b(uint32_t value);

  void set_blinking(uint16_t speed);

 private:
  uint16_t blinking_speed; // 0 = no blink

};

#endif //BGEIGIE_POINTCAST_ESP_LED_H

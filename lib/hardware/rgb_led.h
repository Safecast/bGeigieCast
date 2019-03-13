#ifndef BGEIGIE_POINTCAST_ESP_LED_H
#define BGEIGIE_POINTCAST_ESP_LED_H

#include <Arduino.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB;

class RGBLed {
 public:
  /**
   * Create a RGB led connector
   * @param pin_r: pin connected to RED
   * @param pin_g: pin connected to GREEN
   * @param pin_b: pin connected to BLUE
   * @param reversed: true for anode, false for cathode (default cathode)
   */
  RGBLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, bool reversed = false);
  virtual ~RGBLed() = default;

  void set(RGB& values);

  void off();

  void set_r(uint8_t value);
  void set_g(uint8_t value);
  void set_b(uint8_t value);
 private:
  bool _reversed;
};

#endif //BGEIGIE_POINTCAST_ESP_LED_H

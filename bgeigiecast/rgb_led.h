#ifndef BGEIGIECAST_ESP_LED_H
#define BGEIGIECAST_ESP_LED_H

#include <Arduino.h>

#ifdef STAMPS3
#include <FastLED.h>
#define NUM_LEDS 1

#endif //STAMPS3


typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB_e;  // _e postfix, so it doesn't clash with FastLED lib

class RGBLed {
 public:
#ifdef STAMPS3
  /**
   * Create a FastLED
   * @param ledSerial: fastLED serial connection
   */
  RGBLed();
#else
  /**
   * Create a RGB led connector
   * @param pin_r: pin connected to RED
   * @param pin_g: pin connected to GREEN
   * @param pin_b: pin connected to BLUE
   * @param reversed: true for anode, false for cathode (default cathode)
   */
  RGBLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, bool reversed = false);
#endif //STAMPS3
  virtual ~RGBLed() = default;

  virtual void set(const RGB_e& values);
  virtual void init();
  virtual void off();

  virtual void set_intensity(uint8_t intensity);
  virtual uint8_t get_intensity() const;

 private:
#ifdef STAMPS3
  CRGB leds[1];
#else
  void set_r(uint8_t value);
  void set_g(uint8_t value);
  void set_b(uint8_t value);
  void set_channel(uint8_t channel, uint8_t value);

  bool _reversed;

#endif //STAMPS3
  uint8_t config_intensity;
};

#endif //BGEIGIECAST_ESP_LED_H

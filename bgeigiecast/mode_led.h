#ifndef BGEIGIECAST_STATE_LED_H
#define BGEIGIECAST_STATE_LED_H

#include "rgb_led.h"
#include "i_esp_config.h"

/**
 * Controls the LED to visualize the current state
 */
class ModeLED : private RGBLed{
 public:
  typedef enum {
    off,
    init,
    config,
    mobile,
    fixed_connecting,
    fixed_active,
    fixed_error,
    COUNT
  } ModeColor;


  explicit ModeLED(IEspConfig& config);
  virtual ~ModeLED() = default;

  void set_color(ModeColor color);

  void blink(ModeColor color, double frequency, double percentage_on = 50);

 private:
  typedef struct {
    RGB normal;
    RGB color_blind;
  } ColorType;

  uint8_t get_intensity() const override;

  const IEspConfig& _config;
  bool _blink_state;
  const ColorType _colorTypes[ModeColor::COUNT];
};

#endif //BGEIGIECAST_STATE_LED_H

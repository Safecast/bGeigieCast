#ifndef BGEIGIECAST_ESP_CONFIG_H
#define BGEIGIECAST_ESP_CONFIG_H

#include <Preferences.h>
#include "i_esp_config.h"

/**
 * Configurations for the ESP32, stored in the flash memory
 */
class EspConfig : public IEspConfig {
 public:
  EspConfig();
  virtual ~EspConfig() = default;

  /**
   * Read and set all settings from memory
   */
  void set_all();

  // Getters and setters
  void set_ap_ssid(const char* ap_ssid, bool force) override;
  void set_ap_password(const char* ap_password, bool force) override;
  void set_wifi_ssid(const char* wifi_ssid, bool force) override;
  void set_wifi_password(const char* wifi_password, bool force) override;
  void set_api_key(const char* api_key, bool force) override;
  void set_use_dev(bool use_dev, bool force) override;
  void set_led_color_blind(bool led_color_blind, bool force) override;
  void set_led_color_intensity(uint8_t led_color_intensity, bool force) override;
  void set_saved_state(uint8_t init_fixed, bool force) override;

 protected:
  bool clear() override;

 private:
  Preferences _memory;

};



#endif //BGEIGIECAST_ESP_CONFIG_H

#ifndef BGEIGIE_POINTCAST_I_ESP_CONFIG_H
#define BGEIGIE_POINTCAST_I_ESP_CONFIG_H

#include <cstdint>
#define CONFIG_VAL_MAX 32

/**
 * Abstract class for configurations
 */
class IEspConfig {
 public:
  IEspConfig();
  virtual ~IEspConfig() = default;

  /**
   * Read all settings
   */
  virtual void set_all() = 0;

  /**
   * Reset settings to default (defined in user_config)
   */
  void reset_defaults();

  // Getters and setters
  virtual const char* get_ap_ssid() const final;
  virtual const char* get_ap_password() const final;
  virtual const char* get_wifi_ssid() const final;
  virtual const char* get_wifi_password() const final;
  virtual const char* get_api_key() const final;
  virtual bool get_use_dev() const final;
  virtual bool is_led_color_blind() const final;
  virtual uint8_t get_led_color_intensity() const final;
  virtual uint8_t get_saved_state() const final;

  virtual void set_ap_ssid(const char* ap_ssid, bool force) = 0;
  virtual void set_ap_password(const char* ap_password, bool force) = 0;
  virtual void set_wifi_ssid(const char* wifi_ssid, bool force) = 0;
  virtual void set_wifi_password(const char* wifi_password, bool force) = 0;
  virtual void set_api_key(const char* api_key, bool force) = 0;
  virtual void set_use_dev(bool use_dev, bool force) = 0;
  virtual void set_led_color_blind(bool led_color_blind, bool force) = 0;
  virtual void set_led_color_intensity(uint8_t led_color_intensity, bool force) = 0;
  virtual void set_saved_state(uint8_t saved_state, bool force) = 0;


 protected:
  /**
   * Clear the stored settings (used by reset)
   * @return true if stored settings were cleared
   */
  virtual bool clear() = 0;

  // Access point config (for web _ap_server)
  char _ap_ssid[CONFIG_VAL_MAX];
  char _ap_password[CONFIG_VAL_MAX];

  // Wifi config (to connect to the internet)
  char _wifi_ssid[CONFIG_VAL_MAX];
  char _wifi_password[CONFIG_VAL_MAX];

  // API config (to connect to the API)
  char _api_key[CONFIG_VAL_MAX];
  bool _use_dev;

  // RGB LED config
  bool _led_color_blind;
  uint8_t _led_color_intensity;

  // Flag if fixed or mobile mode is started after init
  uint8_t _saved_state;
};

#endif //BGEIGIE_POINTCAST_I_ESP_CONFIG_H

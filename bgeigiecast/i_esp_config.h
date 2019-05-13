#ifndef BGEIGIECAST_I_ESP_CONFIG_H
#define BGEIGIECAST_I_ESP_CONFIG_H

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
  virtual uint16_t get_device_id() const final;
  virtual const char* get_ap_password() const final;
  virtual const char* get_wifi_ssid() const final;
  virtual const char* get_wifi_password() const final;
  virtual const char* get_api_key() const final;
  virtual bool get_use_dev() const final;
  virtual bool is_led_color_blind() const final;
  virtual uint8_t get_led_color_intensity() const final;
  virtual uint8_t get_saved_state() const final;

  virtual bool get_use_home_location() const final;
  virtual double get_home_longtitude() const final;
  virtual double get_home_latitude() const final;
  virtual double get_last_longtitude() const final;
  virtual double get_last_latitude() const final;

  virtual void set_device_id(uint16_t device_id, bool force) = 0;
  virtual void set_ap_password(const char* ap_password, bool force) = 0;
  virtual void set_wifi_ssid(const char* wifi_ssid, bool force) = 0;
  virtual void set_wifi_password(const char* wifi_password, bool force) = 0;
  virtual void set_api_key(const char* api_key, bool force) = 0;
  virtual void set_use_dev(bool use_dev, bool force) = 0;
  virtual void set_led_color_blind(bool led_color_blind, bool force) = 0;
  virtual void set_led_color_intensity(uint8_t led_color_intensity, bool force) = 0;
  virtual void set_saved_state(uint8_t saved_state, bool force) = 0;
  virtual void set_use_home_location(bool use_home_location, bool force) = 0;
  virtual void set_home_longitude(double home_longitude, bool force) = 0;
  virtual void set_home_latitude(double home_latitude, bool force) = 0;
  virtual void set_last_longitude(double last_longitude, bool force) = 0;
  virtual void set_last_latitude(double last_latitude, bool force) = 0;


 protected:
  /**
   * Clear the stored settings (used by reset)
   * @return true if stored settings were cleared
   */
  virtual bool clear() = 0;

  // Device
  uint16_t _device_id;

  // Access point config (for web _ap_server)
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

  // Home location configs
  bool _use_home_location;
  double _home_longitude;
  double _home_latitude;

  double _last_longitude;
  double _last_latitude;
};

#endif //BGEIGIECAST_I_ESP_CONFIG_H

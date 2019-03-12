#ifndef BGEIGIE_POINTCAST_ESP_CONFIG_H
#define BGEIGIE_POINTCAST_ESP_CONFIG_H

#define CONFIG_VAL_MAX 32

#include <Preferences.h>

/**
 * Configurations for the ESP32, stored in the flash memory
 */
class EspConfig {
 public:
  EspConfig();
  virtual ~EspConfig() = default;

  /**
   * Read all settings
   */
  void set_all();

  /**
   * Reset settings to default (defined in user_config)
   */
  void reset_defaults();

  // Getters and setters
  const char* get_ap_ssid() const;
  void set_ap_ssid(const char* ap_ssid);
  const char* get_ap_password() const;
  void set_ap_password(const char* ap_password);
  const char* get_wifi_ssid() const;
  void set_wifi_ssid(const char* wifi_ssid);
  const char* get_wifi_password() const;
  void set_wifi_password(const char* wifi_password);
  const char* get_api_key() const;
  void set_api_key(const char* api_key);
  bool get_use_dev() const;
  void set_use_dev(bool use_dev);

 private:
  Preferences _memory;
  // Access point config (for web _ap_server)
  char _ap_ssid[CONFIG_VAL_MAX];
  char _ap_password[CONFIG_VAL_MAX];

  // Wifi config (to connect to the internet)
  char _wifi_ssid[CONFIG_VAL_MAX];
  char _wifi_password[CONFIG_VAL_MAX];

  // API config (to connect to the API)
  char _api_key[CONFIG_VAL_MAX];
  bool _use_dev;

};



#endif //BGEIGIE_POINTCAST_ESP_CONFIG_H

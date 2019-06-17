#ifndef BGEIGIE_POINTCAST_TEST_CONFIG_H
#define BGEIGIE_POINTCAST_TEST_CONFIG_H

#include <string.h>
#include <i_esp_config.h>
#include <user_config.h>

/**
 * Test class to inject in the test controller
 */
class TestEspConfig : public IEspConfig {
 public:
  TestEspConfig() = default;
  virtual ~TestEspConfig() = default;

  void set_all() {
    strcpy(_ap_password, D_ACCESS_POINT_PASSWORD);
    strcpy(_wifi_ssid, D_WIFI_SSID);
    strcpy(_wifi_password, D_WIFI_PASSWORD);
    strcpy(_api_key, D_APIKEY);
    _use_dev = D_USE_DEV_SERVER;
    _dev_sped_up = false;
    _led_color_blind = D_LED_COLOR_BLIND;
    _led_color_intensity = D_LED_COLOR_INTENSITY;
    _saved_state = D_SAVED_STATE;
    _use_home_location = false;
    _home_longitude = 0;
    _home_latitude = 0;
    _last_longitude = 0;
    _last_latitude = 0;
  }

  void set_device_id(uint16_t device_id, bool force) override {
    if(force || (device_id != _device_id)) {
      _device_id = device_id;
    }
  }

  void set_ap_password(const char* ap_password, bool force) override {
    if(force || (ap_password != nullptr && strlen(ap_password) < CONFIG_VAL_MAX)) {
      strcpy(_ap_password, ap_password);
    }
  }

  void set_wifi_ssid(const char* wifi_ssid, bool force) override {
    if(force || (wifi_ssid != nullptr && strlen(wifi_ssid) < CONFIG_VAL_MAX)) {
      strcpy(_wifi_ssid, wifi_ssid);
    }
  }

  void set_wifi_password(const char* wifi_password, bool force) override {
    if(force || (wifi_password != nullptr && strlen(wifi_password) < CONFIG_VAL_MAX)) {
      strcpy(_wifi_password, wifi_password);
    }
  }

  void set_api_key(const char* api_key, bool force) override {
    if(force || (api_key != nullptr && strlen(api_key) < CONFIG_VAL_MAX)) {
      strcpy(_api_key, api_key);
    }
  }

  void set_use_dev(bool use_dev, bool force) override {
    if(force || (use_dev != _use_dev)) {
      _use_dev = use_dev;
    }
  }

  void set_dev_sped_up(bool sped_up, bool force) override {
    if(force || (sped_up != _dev_sped_up)) {
      _dev_sped_up = sped_up;
    }
  }

  void set_led_color_blind(bool led_color_blind, bool force) override {
    if(force || (led_color_blind != _led_color_blind)) {
      _led_color_blind = led_color_blind;
    }
  }

  void set_led_color_intensity(uint8_t led_color_intensity, bool force) override {
    if(force || (led_color_intensity != _led_color_intensity)) {
      _led_color_intensity = led_color_intensity;
    }

  }

  void set_saved_state(uint8_t saved_state, bool force) override {
    if(force || (saved_state != _saved_state)) {
      _saved_state = saved_state;
    }
  }

  void set_use_home_location(bool use_home_location, bool force) override {
    if(force || (use_home_location != _use_home_location)) {
      _use_home_location = use_home_location;
    }
  }

  void set_home_longitude(double home_longtitude, bool force) override {
    _home_longitude = home_longtitude;
  }

  void set_home_latitude(double home_latitude, bool force) override {
    _home_latitude = home_latitude;
  }

  void set_last_longitude(double last_longitude, bool force) override {
    _last_longitude = last_longitude;
  }

  void set_last_latitude(double last_latitude, bool force) override {
    _last_latitude = last_latitude;
  }

 protected:
  virtual bool clear() {
    return true;
  }
};

#endif //BGEIGIE_POINTCAST_TEST_CONFIG_H

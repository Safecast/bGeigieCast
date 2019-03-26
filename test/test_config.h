#ifndef BGEIGIE_POINTCAST_TEST_CONFIG_H
#define BGEIGIE_POINTCAST_TEST_CONFIG_H

#include <string.h>
#include <configurations/i_esp_config.h>
#include <user_config.h>

/**
 * Test class to inject in the test controller
 */
class TestEspConfig : public IEspConfig {
 public:
  TestEspConfig() = default;
  virtual ~TestEspConfig() = default;

  virtual void set_all() {
    strcpy(_ap_ssid, D_ACCESS_POINT_SSID);
    strcpy(_ap_password, D_ACCESS_POINT_PASSWORD);
    strcpy(_wifi_ssid, D_WIFI_SSID);
    strcpy(_wifi_password, D_WIFI_PASSWORD);
    strcpy(_api_key, D_APIKEY);
    _use_dev = D_USE_DEV_SERVER;
    _init_stationary = D_INIT_STATIONARY;
  }

  virtual void set_ap_ssid(const char* ap_ssid, bool force) {
    if(force || (ap_ssid != nullptr && strlen(ap_ssid) < CONFIG_VAL_MAX)) {
      strcpy(_ap_ssid, ap_ssid);
    }
  }

  virtual void set_ap_password(const char* ap_password, bool force) {
    if(force || (ap_password != nullptr && strlen(ap_password) < CONFIG_VAL_MAX)) {
      strcpy(_ap_ssid, ap_password);
    }
  }

  virtual void set_wifi_ssid(const char* wifi_ssid, bool force) {
    if(force || (wifi_ssid != nullptr && strlen(wifi_ssid) < CONFIG_VAL_MAX)) {
      strcpy(_ap_ssid, wifi_ssid);
    }
  }

  virtual void set_wifi_password(const char* wifi_password, bool force) {
    if(force || (wifi_password != nullptr && strlen(wifi_password) < CONFIG_VAL_MAX)) {
      strcpy(_ap_ssid, wifi_password);
    }
  }

  virtual void set_api_key(const char* api_key, bool force) {
    if(force || (api_key != nullptr && strlen(api_key) < CONFIG_VAL_MAX)) {
      strcpy(_ap_ssid, api_key);
    }
  }

  virtual void set_use_dev(bool use_dev, bool force) {
    if(force || (use_dev != _use_dev)) {
      _use_dev = use_dev;
    }
  }

  virtual void set_init_stationary(bool init_stationary, bool force) {
    if(force || (init_stationary != _init_stationary)) {
      _init_stationary = init_stationary;
    }
  }

 protected:
  virtual bool clear() {
    return true;
  }
};

#endif //BGEIGIE_POINTCAST_TEST_CONFIG_H

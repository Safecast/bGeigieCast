#include "i_esp_config.h"
#include "user_config.h"

IEspConfig::IEspConfig() :
    _device_id(0),
    _ap_password(""),
    _wifi_ssid(""),
    _wifi_password(""),
    _api_key(""),
    _use_dev(D_USE_DEV_SERVER),
    _led_color_blind(D_LED_COLOR_BLIND),
    _led_color_intensity(D_LED_COLOR_INTENSITY),
    _saved_state(D_SAVED_STATE),
    _use_home_location(false),
    _home_longitude(0),
    _home_latitude(0),
    _last_longitude(0),
    _last_latitude(0) {
}

void IEspConfig::reset_defaults() {
  if(clear()) {
    set_device_id(D_DEVICE_ID, true);
    set_ap_password(D_ACCESS_POINT_PASSWORD, true);
    set_wifi_ssid(D_WIFI_SSID, true);
    set_wifi_password(D_WIFI_PASSWORD, true);
    set_api_key(D_APIKEY, true);
    set_use_dev(D_USE_DEV_SERVER, true);
    set_dev_sped_up(false, true);
    set_led_color_blind(D_LED_COLOR_BLIND, true);
    set_led_color_intensity(D_LED_COLOR_INTENSITY, true);
    set_saved_state(D_SAVED_STATE, true);
    set_use_home_location(false, true);
    set_home_longitude(0, true);
    set_home_latitude(0, true);
  }
}

uint16_t IEspConfig::get_device_id() const {
  return _device_id;
}

const char* IEspConfig::get_ap_password() const {
  return _ap_password;
}

const char* IEspConfig::get_wifi_ssid() const {
  return _wifi_ssid;
}

const char* IEspConfig::get_wifi_password() const {
  return _wifi_password;
}

const char* IEspConfig::get_api_key() const {
  return _api_key;
}

uint8_t IEspConfig::get_saved_state() const {
  return _saved_state;
}

bool IEspConfig::is_led_color_blind() const {
  return _led_color_blind;
}

uint8_t IEspConfig::get_led_color_intensity() const {
  return _led_color_intensity;
}

bool IEspConfig::get_use_dev() const {
  return _use_dev;
}

bool IEspConfig::get_dev_sped_up() const {
  return _dev_sped_up;
}

bool IEspConfig::get_use_home_location() const {
  return _use_home_location;
}

double IEspConfig::get_home_longtitude() const {
  return _home_longitude;
}

double IEspConfig::get_home_latitude() const {
  return _home_latitude;
}

double IEspConfig::get_last_longtitude() const {
  return _last_longitude;
}

double IEspConfig::get_last_latitude() const {
  return _last_latitude;
}

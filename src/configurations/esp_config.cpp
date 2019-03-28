#include <string.h>
#include <esp_spi_flash.h>
#include <stdint.h>

#include "esp_config.h"
#include "debugger.h"

const char* memory_name = "data";

// Keys for config
const char* key_ap_ssid = "ap_ssid";
const char* key_ap_password = "ap_password";
const char* key_wifi_ssid = "wifi_ssid";
const char* key_wifi_password = "wifi_password";
const char* key_api_key = "api_key";
const char* key_use_dev = "use_dev";
const char* key_led_color_blind = "led_color_blind";
const char* key_led_color_intensity = "led_color_intensity";
const char* key_init_stationary = "init_stationary";

EspConfig::EspConfig() :
    IEspConfig::IEspConfig(),
    _memory() {
}

void EspConfig::set_all() {
  _memory.begin(memory_name, true);
  if(_memory.getString(key_ap_ssid, _ap_ssid, CONFIG_VAL_MAX) == 0) {
    strcpy(_ap_ssid, D_ACCESS_POINT_SSID);
  }
  if(_memory.getString(key_ap_password, _ap_password, CONFIG_VAL_MAX) == 0) {
    strcpy(_ap_password, D_ACCESS_POINT_PASSWORD);
  }
  if(_memory.getString(key_wifi_ssid, _wifi_ssid, CONFIG_VAL_MAX) == 0) {
    strcpy(_wifi_ssid, D_WIFI_SSID);
  }
  if(_memory.getString(key_wifi_password, _wifi_password, CONFIG_VAL_MAX) == 0) {
    strcpy(_wifi_password, D_WIFI_PASSWORD);
  }
  if(_memory.getString(key_api_key, _api_key, CONFIG_VAL_MAX) == 0) {
    strcpy(_api_key, D_APIKEY);
  }
  _use_dev = _memory.getBool(key_use_dev, D_USE_DEV_SERVER);
  _led_color_blind = _memory.getBool(key_led_color_blind, D_LED_COLOR_BLIND);
  _led_color_intensity = _memory.getUChar(key_led_color_intensity, D_LED_COLOR_INTENSITY);
  _init_stationary = _memory.getBool(key_init_stationary, D_INIT_STATIONARY);
  _memory.end();
}

bool EspConfig::clear() {
  if(_memory.begin(memory_name)) {
    _memory.clear();
    _memory.end();
    return true;
  }
  return false;
}

void EspConfig::set_ap_ssid(const char* ap_ssid, bool force) {
  if(force || (ap_ssid != nullptr && strlen(ap_ssid) < CONFIG_VAL_MAX)) {
    if(_memory.begin(memory_name)) {
      strcpy(_ap_ssid, ap_ssid);
      _memory.putString(key_ap_ssid, _ap_ssid);
      _memory.end();
    } else {
      debug_println("unable to save new value for ap_ssid");
    }
  }
}

void EspConfig::set_ap_password(const char* ap_password, bool force) {
  if(force || (ap_password != nullptr && strlen(ap_password) < CONFIG_VAL_MAX)) {
    if(_memory.begin(memory_name)) {
      strcpy(_ap_password, ap_password);
      _memory.putString(key_ap_password, _ap_password);
      _memory.end();
    } else {
      debug_println("unable to save new value for ap_password");
    }
  }
}

void EspConfig::set_wifi_ssid(const char* wifi_ssid, bool force) {
  if(force || (wifi_ssid != nullptr && strlen(wifi_ssid) < CONFIG_VAL_MAX)) {
    if(_memory.begin(memory_name)) {
      strcpy(_wifi_ssid, wifi_ssid);
      _memory.putString(key_wifi_ssid, _wifi_ssid);
      _memory.end();
    } else {
      debug_println("unable to save new value for wifi_ssid");
    }
  }
}

void EspConfig::set_wifi_password(const char* wifi_password, bool force) {
  if(force || (wifi_password != nullptr && strlen(wifi_password) < CONFIG_VAL_MAX)) {
    if(_memory.begin(memory_name)) {
      strcpy(_wifi_password, wifi_password);
      _memory.putString(key_wifi_password, _wifi_password);
      _memory.end();
    } else {
      debug_println("unable to save new value for wifi_password");
    }
  }
}

void EspConfig::set_api_key(const char* api_key, bool force) {
  if(force || (api_key != nullptr && strlen(api_key) < CONFIG_VAL_MAX)) {
    if(_memory.begin(memory_name)) {
      strcpy(_api_key, api_key);
      _memory.putString(key_api_key, _api_key);
      _memory.end();
    } else {
      debug_println("unable to save new value for api_key");
    }
  }
}

void EspConfig::set_use_dev(bool use_dev, bool force) {
  if(force || (use_dev != _use_dev)) {
    if(_memory.begin(memory_name)) {
      _use_dev = use_dev;
      _memory.putBool(key_use_dev, use_dev);
      _memory.end();
    } else {
      debug_println("unable to save new value for use_dev");
    }
  }
}

void EspConfig::set_led_color_blind(bool led_color_blind, bool force) {
  if(force || (led_color_blind != _led_color_blind)) {
    if(_memory.begin(memory_name)) {
      _led_color_blind = led_color_blind;
      _memory.putBool(key_led_color_blind, led_color_blind);
      _memory.end();
    } else {
      debug_println("unable to save new value for key_led_color_blind");
    }
  }
}

void EspConfig::set_led_color_intensity(uint8_t led_color_intensity, bool force) {
  if(force || (led_color_intensity != _led_color_intensity)) {
    if(_memory.begin(memory_name)) {
      _led_color_intensity = led_color_intensity;
      _memory.putUChar(key_led_color_intensity, led_color_intensity);
      _memory.end();
    } else {
      debug_println("unable to save new value for key_led_color_intensity");
    }
  }

}

void EspConfig::set_init_stationary(bool init_stationary, bool force) {
  if(force || (init_stationary != _init_stationary)) {
    if(_memory.begin(memory_name)) {
      _init_stationary = init_stationary;
      _memory.putBool(key_init_stationary, init_stationary);
      _memory.end();
    } else {
      debug_println("unable to save new value for init_stationary");
    }
  }
}

#include <string.h>
#include <esp_spi_flash.h>
#include <stdint.h>

#include "esp_config.h"
#include "debugger.h"

const char* memory_name = "data";

// Keys for config
const char* key_device_id = "ap_ssid";
const char* key_ap_password = "ap_password";
const char* key_wifi_ssid = "wifi_ssid";
const char* key_wifi_password = "wifi_password";
const char* key_api_key = "api_key";
const char* key_use_dev = "use_dev";
const char* key_led_color_blind = "led_color_blind";
const char* key_led_color_intensity = "led_intensity";
const char* key_saved_state = "saved_state";
const char* key_home_longtitude = "home_longtitude";
const char* key_home_latitude = "home_latitude";

EspConfig::EspConfig() :
    IEspConfig::IEspConfig(),
    _memory() {
}

void EspConfig::set_all() {
  _memory.begin(memory_name, true);
  _device_id = _memory.getUShort(key_device_id, D_DEVICE_ID);
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
  _saved_state = _memory.getUChar(key_saved_state, D_SAVED_STATE);
  _use_home_location = _memory.getBool(key_led_color_blind, false);
  _home_longitude = _memory.getDouble(key_home_longtitude, 0);
  _home_latitude = _memory.getDouble(key_home_latitude, 0);
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

void EspConfig::set_device_id(uint16_t device_id, bool force) {
  if(force || (device_id != _device_id)) {
    if(_memory.begin(memory_name)) {
      _device_id = device_id;
      _memory.putUShort(key_device_id, _device_id);
      _memory.end();
    } else {
      DEBUG_PRINTLN("unable to save new value for device_id");
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
      DEBUG_PRINTLN("unable to save new value for ap_password");
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
      DEBUG_PRINTLN("unable to save new value for wifi_ssid");
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
      DEBUG_PRINTLN("unable to save new value for wifi_password");
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
      DEBUG_PRINTLN("unable to save new value for api_key");
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
      DEBUG_PRINTLN("unable to save new value for use_dev");
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
      DEBUG_PRINTLN("unable to save new value for key_led_color_blind");
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
      DEBUG_PRINTLN("unable to save new value for key_led_color_intensity");
    }
  }

}

void EspConfig::set_saved_state(uint8_t saved_state, bool force) {
  if(force || (saved_state != _saved_state)) {
    if(_memory.begin(memory_name)) {
      _saved_state = saved_state;
      _memory.putUChar(key_saved_state, saved_state);
      _memory.end();
    } else {
      DEBUG_PRINTLN("unable to save new value for init_fixed");
    }
  }
}

void EspConfig::set_use_home_location(bool use_home_location, bool force) {
  if(force || (use_home_location != _use_home_location)) {
    if(_memory.begin(memory_name)) {
      _use_home_location = use_home_location;
      _memory.putBool(key_led_color_blind, use_home_location);
      _memory.end();
    } else {
      DEBUG_PRINTLN("unable to save new value for key_led_color_blind");
    }
  }
}

void EspConfig::set_home_longitude(double home_longtitude, bool force) {
  if(_memory.begin(memory_name)) {
    _home_longitude = home_longtitude;
    _memory.putDouble(key_home_longtitude, home_longtitude);
    _memory.end();
  } else {
    DEBUG_PRINTLN("unable to save new value for key_home_longtitude");
  }
}

void EspConfig::set_home_latitude(double home_latitude, bool force) {
  if(_memory.begin(memory_name)) {
    _home_latitude = home_latitude;
    _memory.putDouble(key_home_latitude, home_latitude);
    _memory.end();
  } else {
    DEBUG_PRINTLN("unable to save new value for key_home_latitude");
  }
}

void EspConfig::set_last_longitude(double current_longtitude, bool force) {
  _last_longitude = current_longtitude;
}

void EspConfig::set_last_latitude(double current_latitude, bool force) {
  _last_latitude = current_latitude;
}

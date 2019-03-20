#include <string.h>
#include <esp_spi_flash.h>
#include <stdint.h>

#include "esp_config.h"
#include "user_config.h"
#include "debugger.h"

const char* memory_name = "data";

// Keys for config
const char* key_ap_ssid = "ap_ssid";
const char* key_ap_password = "ap_password";
const char* key_wifi_ssid = "wifi_ssid";
const char* key_wifi_password = "wifi_password";
const char* key_api_key = "api_key";
const char* key_use_dev = "use_dev";
const char* key_init_stationary = "init_stationary";

EspConfig::EspConfig() :
    _memory(),
    _ap_ssid(""),
    _ap_password(""),
    _wifi_ssid(""),
    _wifi_password(""),
    _api_key(""),
    _use_dev(D_USE_DEV_SERVER),
    _init_stationary(D_INIT_STATIONARY) {
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
  _init_stationary = _memory.getBool(key_init_stationary, D_INIT_STATIONARY);
  _memory.end();
}

void EspConfig::reset_defaults() {
  if(_memory.begin(memory_name)) {
    _memory.clear();
    _memory.end();
    set_ap_ssid(D_ACCESS_POINT_SSID, true);
    set_ap_password(D_ACCESS_POINT_PASSWORD, true);
    set_wifi_ssid(D_WIFI_SSID, true);
    set_wifi_password(D_WIFI_PASSWORD, true);
    set_api_key(D_APIKEY, true);
    set_use_dev(D_USE_DEV_SERVER, true);
    set_init_stationary(D_INIT_STATIONARY, true);
  }
}

const char* EspConfig::get_ap_ssid() const {
  return _ap_ssid;
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

const char* EspConfig::get_ap_password() const {
  return _ap_password;
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

const char* EspConfig::get_wifi_ssid() const {
  return _wifi_ssid;
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

const char* EspConfig::get_wifi_password() const {
  return _wifi_password;
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

const char* EspConfig::get_api_key() const {
  return _api_key;
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

bool EspConfig::get_use_dev() const {
  return _use_dev;
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

bool EspConfig::is_init_stationary() const {
  return _init_stationary;
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

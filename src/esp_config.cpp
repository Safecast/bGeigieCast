#include <string.h>
#include <esp_spi_flash.h>
#include <stdint.h>

#include "esp_config.h"
#include "user_config.h"
#include "debugger.h"

// Keys for config
const char* key_ap_ssid = "ap_ssid";
const char* key_ap_password = "ap_password";
const char* key_wifi_ssid = "wifi_ssid";
const char* key_wifi_password = "wifi_password";
const char* key_api_key = "api_key";
const char* key_use_dev = "use_dev";

EspConfig::EspConfig() :
    _memory(),
    _ap_ssid(),
    _ap_password(),
    _wifi_ssid(),
    _wifi_password(),
    _api_key(),
    _use_dev() {
}

void EspConfig::set_all() {
  _memory.begin("data");
  if(_memory.getString(key_ap_ssid, _ap_ssid, CONFIG_VAL_MAX) == 0) {
    debug_print("Key ");
    debug_print(key_ap_ssid);
    debug_print(" did not return any value, using default");
    debug_println(D_ACCESS_POINT_SSID);
    strcpy(_ap_ssid, D_ACCESS_POINT_SSID);
  }
  if(_memory.getString(key_ap_password, _ap_password, CONFIG_VAL_MAX) == 0) {
    debug_print("Key ");
    debug_print(key_ap_password);
    debug_print(" did not return any value, using default");
    debug_println(D_ACCESS_POINT_PASSWORD);
    strcpy(_ap_password, D_ACCESS_POINT_PASSWORD);
  }
  if(_memory.getString(key_wifi_ssid, _wifi_ssid, CONFIG_VAL_MAX) == 0) {
    debug_print("Key ");
    debug_print(key_wifi_ssid);
    debug_print(" did not return any value, using default");
    debug_println(D_WIFI_SSID);
    strcpy(_wifi_ssid, D_WIFI_SSID);
  }
  if(_memory.getString(key_wifi_password, _wifi_password, CONFIG_VAL_MAX) == 0) {
    debug_print("Key ");
    debug_print(key_wifi_password);
    debug_print(" did not return any value, using default");
    debug_println(D_WIFI_PASSWORD);
    strcpy(_wifi_password, D_WIFI_PASSWORD);
  }
  if(_memory.getString(key_api_key, _api_key, CONFIG_VAL_MAX) == 0) {
    debug_print("Key ");
    debug_print(key_api_key);
    debug_print(" did not return any value, using default");
    debug_println(D_APIKEY);
    strcpy(_api_key, D_APIKEY);
  }
  _use_dev = _memory.getBool(key_use_dev, D_USE_DEV_SERVER);
  _memory.end();
}

void EspConfig::reset_defaults() {
  set_ap_ssid(D_ACCESS_POINT_SSID);
  set_ap_password(D_ACCESS_POINT_PASSWORD);
  set_wifi_ssid(D_WIFI_SSID);
  set_wifi_password(D_WIFI_PASSWORD);
  set_api_key(D_APIKEY);
  set_use_dev(D_USE_DEV_SERVER);
  _memory.end();
}

int EspConfig::get_ap_ssid(char* out) const {
  strcpy(out, _ap_ssid);
  return strlen(_ap_ssid);
}

void EspConfig::set_ap_ssid(const char* ap_ssid) {
  if(ap_ssid != nullptr && strlen(ap_ssid) < CONFIG_VAL_MAX) {
    _memory.begin("data");
    strcpy(_ap_ssid, ap_ssid);
    _memory.putString(key_ap_ssid, _ap_ssid);
    _memory.end();
  }
}

int EspConfig::get_ap_password(char* out) const {
  strcpy(out, _ap_password);
  return strlen(_ap_password);
}

void EspConfig::set_ap_password(const char* ap_password) {
  if(ap_password != nullptr && strlen(ap_password) < CONFIG_VAL_MAX) {
    _memory.begin("data");
    strcpy(_ap_password, ap_password);
    _memory.putString(key_ap_password, _ap_password);
    _memory.end();
  }
}

int EspConfig::get_wifi_ssid(char* out) const {
  strcpy(out, _wifi_ssid);
  return strlen(_wifi_ssid);
}

void EspConfig::set_wifi_ssid(const char* wifi_ssid) {
  if(wifi_ssid != nullptr && strlen(wifi_ssid) < CONFIG_VAL_MAX) {
    _memory.begin("data");
    strcpy(_wifi_ssid, wifi_ssid);
    _memory.putString(key_wifi_ssid, _wifi_ssid);
    _memory.end();
  }
}

int EspConfig::get_wifi_password(char* out) const {
  strcpy(out, _wifi_password);
  return strlen(_wifi_password);
}

void EspConfig::set_wifi_password(const char* wifi_password) {
  if(wifi_password != nullptr && strlen(wifi_password) < CONFIG_VAL_MAX) {
    _memory.begin("data");
    strcpy(_wifi_password, wifi_password);
    _memory.putString(key_wifi_password, _wifi_password);
    _memory.end();
  }
}

int EspConfig::get_api_key(char* out) const {
  strcpy(out, _api_key);
  return strlen(_api_key);
}

void EspConfig::set_api_key(const char* api_key) {
  if(api_key != nullptr && strlen(api_key) < CONFIG_VAL_MAX) {
    _memory.begin("data");
    strcpy(_api_key, api_key);
    _memory.putString(key_api_key, _api_key);
    _memory.end();
  }
}

bool EspConfig::get_use_dev() const {
  return _use_dev;
}

void EspConfig::set_use_dev(bool use_dev) {
  if(use_dev != _use_dev) {
    _memory.begin("data");
    _use_dev = use_dev;
    _memory.putBool(key_use_dev, use_dev);
    _memory.end();
  }
}

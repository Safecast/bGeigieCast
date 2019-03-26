#include "i_esp_config.h"
#include "user_config.h"

IEspConfig::IEspConfig() :
    _ap_ssid(""),
    _ap_password(""),
    _wifi_ssid(""),
    _wifi_password(""),
    _api_key(""),
    _use_dev(D_USE_DEV_SERVER),
    _init_stationary(D_INIT_STATIONARY) {

}

void IEspConfig::reset_defaults() {
  if(clear()) {
    set_ap_ssid(D_ACCESS_POINT_SSID, true);
    set_ap_password(D_ACCESS_POINT_PASSWORD, true);
    set_wifi_ssid(D_WIFI_SSID, true);
    set_wifi_password(D_WIFI_PASSWORD, true);
    set_api_key(D_APIKEY, true);
    set_use_dev(D_USE_DEV_SERVER, true);
    set_init_stationary(D_INIT_STATIONARY, true);
  }
}

const char* IEspConfig::get_ap_ssid() const {
  return _ap_ssid;
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

bool IEspConfig::is_init_stationary() const {
  return _init_stationary;
}

bool IEspConfig::get_use_dev() const {
  return _use_dev;
}
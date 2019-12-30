
#include <ESPmDNS.h>

#include "access_point.h"
#include "identifiers.h"
#include "wifi_connection.h"
#include "debugger.h"

AccessPoint::AccessPoint(LocalStorage& config) :
    Worker<bool>(k_worker_wifi_access_point, false),
    _config(config){

}

int8_t AccessPoint::produce_data() {
  return 0;
}

bool AccessPoint::activate(bool) {
  auto device_id = _config.get_device_id();
  if(!device_id) {
    DEBUG_PRINTLN("Can't start config without device id!");
    return false;
  }

  char host_ssid[16];
  sprintf(host_ssid, ACCESS_POINT_SSID, device_id);
  MDNS.begin(host_ssid);

  return WiFiConnection::start_ap_server(host_ssid, _config.get_ap_password());
}

void AccessPoint::deactivate() {
  WiFiConnection::stop_ap_server();
}


#include "access_point.h"
#include "identifiers.h"
#include "wifi_connection.h"
#include "debugger.h"
#include "http_pages.h"

AccessPoint::AccessPoint(LocalStorage& config) :
    Worker<bool>(false, 0),
    _config(config) {
}

int8_t AccessPoint::produce_data() {
  return BaseWorker::e_worker_idle;
}

bool AccessPoint::activate(bool) {
  // In access point mode there is no internet access
  HttpPages::internet_access = false;
  auto device_id = _config.get_device_id();
  if(!device_id) {
    DEBUG_PRINTLN("Can't start config without device id!");
    return false;
  }

  char host_ssid[16];
  sprintf(host_ssid, ACCESS_POINT_SSID, device_id);

  return WiFiConnection::start_ap_server(host_ssid, _config.get_ap_password());
}

void AccessPoint::deactivate() {
  // re-set internet access to true, as the access point is no longer in use
  HttpPages::internet_access = true;
  WiFiConnection::stop_ap_server();
}

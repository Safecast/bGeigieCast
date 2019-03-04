#include "api_connector.h"
#include "debugger.h"

ApiConnector::ApiConnector(EspConfig& config) : config(config) {
}

bool ApiConnector::start_connect() {
  char ssid[32], password[32];
  if(!config.get_wifi_ssid(ssid)) {
    debug_println("No SSID to connect to!");
    return false;
  }
  if(config.get_wifi_password(password)) {
    debug_print("Connecting to wifi ssid: \"");
    debug_print(ssid);
    debug_print("\", using password: ");
    debug_println(password);
    WiFi.begin(ssid, password);
  } else {
    debug_print("Connecting to wifi ssid: ");
    debug_print(ssid);
    debug_println(", using no password");
    WiFi.begin(ssid);
  }

  return is_connected();
}

void ApiConnector::stop() {
  WiFi.disconnect(true, true);
}

bool ApiConnector::test() {
  WiFiClient client;
  return client.connect(API_PING_TEST_ADDRESS, 80) != 0;
}

bool ApiConnector::is_connected() {
  return WiFi.status() == WL_CONNECTED;
}

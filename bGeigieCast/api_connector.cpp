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
    Serial.print("Connecting to wifi ssid: \"");
    Serial.print(ssid);
    Serial.print("\", and password: ");
    Serial.println(password);
    WiFi.begin(ssid, password);
  } else {
    Serial.print("Connecting to wifi ssid: ");
    Serial.print(ssid);
    Serial.println(" and no password");
    WiFi.begin(ssid);
  }

  return is_connected();
}

void ApiConnector::stop() {
  WiFi.disconnect(true, true);
}

bool ApiConnector::test() {
  WiFiClient client;
  if(client.connect(API_PING_TEST_ADDRESS, 80)) {
    Serial.println("API test success");
    return true;
  }
  Serial.println("API test failed");
  return false;
}

bool ApiConnector::is_connected() {
  return WiFi.status() == WL_CONNECTED;
}

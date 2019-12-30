#include <WiFi.h>
#include <Arduino.h>

#include "wifi_connection.h"
#include "debugger.h"

WiFiConnection::WiFiConnection() {}

bool WiFiConnection::connect_wifi(const char* ssid, const char* password) const {
  if(!ssid) {
    DEBUG_PRINTLN("WiFi connector: No SSID to connect to!");
    return false;
  }
  DEBUG_PRINTLN("WiFi connector: Trying to connect to wifi...");
  switch(WiFi.status()) {
    case WL_CONNECTED:
      return true;
    case WL_IDLE_STATUS:
    case WL_DISCONNECTED:
      WiFi.reconnect();
      delay(100);
      return WiFi.isConnected();
    default:
      password ? WiFi.begin(ssid, password) : WiFi.begin(ssid);
      return WiFi.isConnected();
  }
}

void WiFiConnection::disconnect_wifi() const {
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_MODE_NULL);
}

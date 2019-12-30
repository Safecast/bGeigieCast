#ifndef BGEIGIECAST_WIFI_CONNECTION_H_
#define BGEIGIECAST_WIFI_CONNECTION_H_

class WiFiConnection {
 protected:
  WiFiConnection();

  bool connect_wifi(const char* ssid, const char* password = nullptr) const;
  void disconnect_wifi() const;
};

#endif //BGEIGIECAST_WIFI_CONNECTION_H_

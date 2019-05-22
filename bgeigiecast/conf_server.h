#ifndef BGEIGIECAST_SERVER_H
#define BGEIGIECAST_SERVER_H

#include <WiFi.h>
#include <WebServer.h>

#include "esp_config.h"

/**
 * Class to host a web server for configuring the ESP32. Will set up an access
 * point based on user_config.h "Access point settings".
 */
class ConfigWebServer {
 public:
  explicit ConfigWebServer(IEspConfig& config);
  virtual ~ConfigWebServer() = default;

  /**
   * Initialize the web server, does nothing if it is already initialized.
   * @return true if initialization was success
   */
  bool initialize();

  /**
   * Stop the web server
   */
  void stop();

  /**
   * Checks if there are requests and handles them
   */
  void handle_requests();
 private:

  /**
   * Try to connect to the wifi
   * @return success
   */
  bool connect_wifi();

  /**
   * Start access point server
   * @return success
   */
  bool start_ap_server(const char* host_ssid);

  /**
   * Set the endpoints for the server
   */
  void set_endpoints();

  /**
   * Handles request for `/`
   */
  void handle_root();
  /**
   * Handles request for `/save`
   */
  void handle_save();
  /**
   * Handles request for `/update`
   */
  void handle_update_retrieve();
  /**
   * Handles request for `/update` post
   */
  void handle_update_uploading();
  /**
   * Handles request for `/update` when its complete
   */
  void handle_update_complete();

  WebServer _server;
  IEspConfig& _config;

};

#endif //BGEIGIECAST_SERVER_H

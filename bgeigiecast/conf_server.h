#ifndef BGEIGIECAST_SERVER_H
#define BGEIGIECAST_SERVER_H

#include <WiFi.h>
#include <WebServer.h>

#include "esp_config.h"
#include "http_request.h"

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

//  WiFiServer _server;
  WebServer _server;
  IEspConfig& _config;

};

#endif //BGEIGIECAST_SERVER_H

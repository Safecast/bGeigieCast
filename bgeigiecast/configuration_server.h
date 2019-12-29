#ifndef BGEIGIECAST_SERVER_H
#define BGEIGIECAST_SERVER_H

#include <WiFi.h>
#include <WebServer.h>

#include <Worker.hpp>

#include "local_storage.h"


struct ServerStatus {
  bool connected;
  bool running;
};

/**
 * Class to host a web server for configuring the ESP32. Will set up an access
 * point based on user_config.h "Access point settings".
 */
class ConfigWebServer : public Worker<ServerStatus> {
 public:
  explicit ConfigWebServer(LocalStorage& config);
  virtual ~ConfigWebServer() = default;

  /**
   * Checks if there are requests and handles them
   */
  int8_t produce_data();

  /**
   * Initialize the web server and endpoints
   */
  void add_urls();

 protected:
  /**
   * Initialize the web server, does nothing if it is already initialized.
   * @return true if initialization was success
   */
  bool activate(bool retry) override;

  /**
   * Stops the web server
   */
  void deactivate() override;

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
   * Handles request for `/save`
   */
  void handle_save();

  /**
   * Handles request for `/update` post
   */
  void handle_update_uploading();

  WebServer _server;
  LocalStorage& _config;

  bool _running;
};

#endif //BGEIGIECAST_SERVER_H

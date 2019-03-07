#ifndef BGEIGIE_POINTCAST_APICONNECTOR_H
#define BGEIGIE_POINTCAST_APICONNECTOR_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_config.h"

/**
 * Connects over WiFi to the API to send readings
 */
class ApiConnector {
 public:
  explicit ApiConnector(EspConfig& config);
  virtual ~ApiConnector() = default;

  /**
   * Initialize the connection
   * @return true if connection with the wifi was made
   */
  bool start_connect();

  /**
   * Disconnect
   */
  void stop();

  /**
   * Test the connection to the API
   */
  bool test();

  /**
   * Check if the connection is up
   * @return true if connected
   */
  bool is_connected();

 private:
  EspConfig& config;
};

#endif //BGEIGIE_POINTCAST_APICONNECTOR_H

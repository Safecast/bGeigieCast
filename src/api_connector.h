#ifndef BGEIGIE_POINTCAST_APICONNECTOR_H
#define BGEIGIE_POINTCAST_APICONNECTOR_H

#include <WiFi.h>
#include <HTTPClient.h>

#include <circular_buffer.h>

#include "user_config.h"
#include "esp_config.h"
#include "reading.h"

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

  /**
   * Process a new reading. will merge with existing readings and if its time, it will be posted to the API
   * @param reading: new reading to process
   */
  void process_reading(Reading& reading);
 private:

  /**
   * When a reading cannot be send to the API, we save it to send later..
   * @param reading: reading to save
   */
  void save_reading(Reading& reading);

  /**
   * Send a reading to the API
   * @param reading: reading to send
   * @return: true if the API call was successful
   */
  bool send_reading(Reading& reading);

  EspConfig& config;
  CircularBuffer<Reading*, MAX_MISSED_READINGS> missed_readings;

  uint32_t last_send;
  Reading merged_reading;
};

#endif //BGEIGIE_POINTCAST_APICONNECTOR_H

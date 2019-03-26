#ifndef BGEIGIE_POINTCAST_I_APICONNECTOR_H
#define BGEIGIE_POINTCAST_I_APICONNECTOR_H

#include <circular_buffer.h>

#include "../user_config.h"
#include "../configurations/i_esp_config.h"
#include "../reading.h"

/**
 * Connects over WiFi to the API to send readings
 */
class IApiConnector {
 public:
  explicit IApiConnector(IEspConfig& config);
  virtual ~IApiConnector() = default;

  /**
   *
   * Initialize the connection
   * @param initial: set to false if its for reconnect / connect in error
   * @return true if connection with the wifi was made
   */
  virtual bool start_connect(bool initial) = 0;

  /**
   * Disconnect
   */
  virtual void stop() = 0;

  /**
   * Test the connection to the API
   */
  virtual bool test() = 0;

  /**
   * Check if the connection is up
   * @return true if connected
   */
  virtual bool is_connected() = 0;

  /**
   * Process a new reading. will merge with existing readings and if its time, it will be posted to the API
   * @param reading: new reading to process
   */
  virtual void process_reading(Reading& reading) final;

 protected:

  virtual bool time_to_send();

  /**
   * Send a reading to the API
   * @param reading: reading to send
   * @return: true if the API call was successful
   */
  virtual bool send_reading(Reading& reading) = 0;

  /**
   * When a reading cannot be send to the API, we save it to send later..
   * @param reading: reading to save
   */
  virtual void save_reading(Reading& reading) final;

  IEspConfig& config;
  Reading merged_reading;
  uint32_t last_send;

  CircularBuffer<Reading*, MAX_MISSED_READINGS> missed_readings;
};

#endif //BGEIGIE_POINTCAST_I_APICONNECTOR_H

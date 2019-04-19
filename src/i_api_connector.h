#ifndef BGEIGIECAST_I_APICONNECTOR_H
#define BGEIGIECAST_I_APICONNECTOR_H


#include "circular_buffer.h"
#include "user_config.h"
#include "i_esp_config.h"
#include "reading.h"
#include "sm_context.h"

/**
 * Abstract class to be used in controller as a Api connector
 */
class IApiConnector : public Context {
 public:

  typedef enum {
    k_report_skipped,
    k_report_failed,
    k_report_success,
  } ReportApiStatus;

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
  virtual void process_reading(Reading* reading) final;

  uint32_t time_since_last_send() const;

 protected:

  /**
   * Check if enough time has passed to send the latest reading to api
   * @return
   */
  bool time_to_send() const;

  /**
   * Send a reading to the API
   * @param reading: reading to send
   * @return: true if the API call was successful
   */
  virtual bool send_reading(Reading* reading) = 0;

  /**
   * When a reading cannot be send to the API, we save it to send later..
   * @param reading: reading to save
   */
  virtual void save_reading(Reading* reading) final;

  IEspConfig& config;
  CircularBuffer<Reading*, MAX_MISSED_READINGS> missed_readings;
  uint32_t last_send;
  Reading merged_reading;


  friend class PublishApiState;

};

#endif //BGEIGIECAST_I_APICONNECTOR_H

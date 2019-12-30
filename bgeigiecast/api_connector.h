#ifndef BGEIGIECAST_APICONNECTOR_H
#define BGEIGIECAST_APICONNECTOR_H

#include <WiFi.h>
#include <HTTPClient.h>

#include <Handler.hpp>

#include "local_storage.h"
#include "reading.h"
#include "user_config.h"
#include "circular_buffer.h"
#include "wifi_connection.h"

/**
 * Connects over WiFi to the API to send readings
 */
class ApiReporter : private WiFiConnection, public Handler {
 public:

  enum ApiHandlerStatus {
    e_api_reporter_idle,
    e_api_reporter_send_success,
    e_api_reporter_error_invalid_reading,
    e_api_reporter_error_not_connected,
    e_api_reporter_error_remote_not_available,
    e_api_reporter_error_server_rejected_post,
  };

  explicit ApiReporter(LocalStorage& config);
  virtual ~ApiReporter() = default;

 protected:

  /**
   * Check if enough time has passed to send the latest reading to api
   * @return
   */
  bool time_to_send() const;

  /**
   * reset the api time and merged readings
   */
  void reset();

  /**
   * Initialize the connection
   * @param initial: set to false if its for reconnect / connect in error
   * @return true if connection with the wifi was made
   */
  bool activate(bool retry) override;

  /**
   * Stop the connection
   */
  void deactivate() override;

  int8_t handle_produced_work(const worker_status_t& worker_reports) override;
  /**
   * When a reading cannot be send to the API, we save it to send later..
   * @param reading: reading to save
   */
  virtual void save_reading() final;

 private:

  /**
   * Send a reading to the API
   * @param reading: reading to send
   * @return: true if the API call was successful
   */
  ApiHandlerStatus send_reading(const Reading& reading);


  LocalStorage& _config;
  CircularBuffer<Reading, MAX_MISSED_READINGS> _saved_readings;
  uint32_t _last_send;
  Reading _merged_reading;
  ApiHandlerStatus _current_default_response;

  bool _alert;
};

#endif //BGEIGIECAST_APICONNECTOR_H

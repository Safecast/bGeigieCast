#ifndef BGEIGIECAST_APICONNECTOR_H
#define BGEIGIECAST_APICONNECTOR_H

#include <WiFi.h>
#include <HTTPClient.h>

#include "i_api_connector.h"

/**
 * Connects over WiFi to the API to send readings
 */
class ApiConnector : public IApiConnector {
 public:

  explicit ApiConnector(IEspConfig& config, ApiConnectionObserver* observer = nullptr);
  virtual ~ApiConnector() = default;

  /**
   *
   * Initialize the connection
   * @param initial: set to false if its for reconnect / connect in error
   * @return true if connection with the wifi was made
   */
  bool start_connect() override;

  void disconnect() override;
  void stop() override;

  /**
   * Test the connection to the API
   */
  bool retrieve_endpoint() override;

  /**
   * Check if the connection is up
   * @return true if connected
   */
  bool is_connected() override;

  /**
   * Checks if the endpoint DNS is resolved
   * @return
   */
  bool api_endpoint_resolved() const override;

 protected:

  /**
   * Send a reading to the API
   * @param reading: reading to send
   * @return: true if the API call was successful
   */
  bool send_reading(Reading* reading) override;

  void perform_connect();

  IPAddress _api_endpoint;
};

#endif //BGEIGIECAST_APICONNECTOR_H

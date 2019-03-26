#ifndef BGEIGIE_POINTCAST_I_BLUETOOTH_CONNECTOR_H
#define BGEIGIE_POINTCAST_I_BLUETOOTH_CONNECTOR_H

#include "stdint.h"
#include "../reading.h"

/**
 * Abstract bluetooth connector to inject
 */
class IBluetoohConnector {
 public:
  IBluetoohConnector() : initialized(false) {
  }
  virtual ~IBluetoohConnector() = default;

  /**
   * Initialize the bluetooth, using device id as name
   * @param device_id : id of the bgeigie device
   */
  virtual void init(uint16_t device_id) = 0;

  /**
   * Send a new reading over bluetooth
   * @param reading : reading object to send
   */
  virtual void send_reading(Reading& reading) = 0;
 protected:
  bool initialized;
};

#endif //BGEIGIE_POINTCAST_I_BLUETOOTH_CONNECTOR_H

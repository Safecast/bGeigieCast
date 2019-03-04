#ifndef BGEIGIE_POINTCAST_BGEIGIE_CONNECTOR_H
#define BGEIGIE_POINTCAST_BGEIGIE_CONNECTOR_H

#include <Arduino.h>

class BGeigieConnector {
 public:
  explicit BGeigieConnector(HardwareSerial& _serial_connection);
  virtual ~BGeigieConnector() = default;

  /**
   * Get a reading from serial
   * @param out: output for the reading
   * @return: true if a reading was read
   */
  bool get_reading(char* out);

 private:
  HardwareSerial& _serial_connection;
};

#endif //BGEIGIE_POINTCAST_BGEIGIE_CONNECTOR_H

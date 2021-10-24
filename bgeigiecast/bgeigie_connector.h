#ifndef BGEIGIECAST_BGEIGIE_CONNECTOR_H
#define BGEIGIECAST_BGEIGIE_CONNECTOR_H

#include <Arduino.h>

#include "Worker.hpp"

#include "reading.h"

/**
 * Connect the system to the bGeigieNano to read sensor data
 */
class BGeigieConnector : public Worker<Reading> {
 public:
  explicit BGeigieConnector(Stream& _serial_connection);
  virtual ~BGeigieConnector() = default;

  int8_t produce_data() override;

 private:
  Stream& _serial_connection;
  String _buffer;
};

#endif //BGEIGIECAST_BGEIGIE_CONNECTOR_H

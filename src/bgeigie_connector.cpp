#include "bgeigie_connector.h"
#include "user_config.h"
#include "debugger.h"

BGeigieConnector::BGeigieConnector(HardwareSerial& serial_connection) : _serial_connection(serial_connection) {
  _serial_connection.begin(BGEIGIE_CONNECTION_BAUD);
}

bool BGeigieConnector::get_reading(Reading** out) {
  if(_serial_connection.available() > 0) {
    String str = _serial_connection.readString();
    *out = new Reading(str.c_str());
    return true;
  }
  return false;
}

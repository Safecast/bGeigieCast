#include "bgeigie_connector.h"
#include "user_config.h"
#include "debugger.h"

BGeigieConnector::BGeigieConnector(HardwareSerial& serial_connection) : _serial_connection(serial_connection) {
  _serial_connection.begin(BGEIGIE_CONNECTION_BAUD);
}

bool BGeigieConnector::get_reading(char* out) {
  if(_serial_connection.available() > 0) {
    String read = _serial_connection.readString();
    debug_println(read);
    strcpy(out, read.c_str());
    return true;
  }
  return false;
}

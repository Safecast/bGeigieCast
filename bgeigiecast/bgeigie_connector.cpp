#include "bgeigie_connector.h"
#include "user_config.h"
#include "debugger.h"

BGeigieConnector::BGeigieConnector(Stream& serial_connection) : _serial_connection(serial_connection), _buffer("") {
}

bool BGeigieConnector::get_reading(Reading** out) {
  while(_serial_connection.available() > 0) {
    char c = static_cast<char>(_serial_connection.read());
    _buffer += c;
    if(c == '\n') {
//      DEBUG_PRINT("New reading: "); DEBUG_PRINT(_buffer);
      *out = new Reading(_buffer.c_str());
      _buffer = "";
      return true;
    }
  }
  return false;
}

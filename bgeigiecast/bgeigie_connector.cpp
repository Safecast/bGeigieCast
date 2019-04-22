#include "bgeigie_connector.h"
#include "user_config.h"
#include "debugger.h"

BGeigieConnector::BGeigieConnector(Stream& serial_connection) : _serial_connection(serial_connection) {
}

bool BGeigieConnector::get_reading(Reading** out) {
  if(_serial_connection.available() > 0) {
    String str = _serial_connection.readStringUntil('\n');
    str += '\n';
    *out = new Reading(str.c_str());
    DEBUG_PRINTLN(str);
    return true;
  }
  return false;
}

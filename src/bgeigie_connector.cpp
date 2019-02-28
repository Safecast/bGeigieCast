#include "bgeigie_connector.h"

BGeigieConnector::BGeigieConnector(HardwareSerial& serial_connection) : _serial_connection(serial_connection) {
  _serial_connection.begin(9600);
}

bool BGeigieConnector::get_reading(char* out) {
  if(_serial_connection.available() > 0) {
    String read = Serial.readStringUntil('\n');

    // Log what we got..
    Serial.print("Received: ");
    Serial.println(read);

    strcpy(out, read.c_str());
    return true;
  }
  return false;
}

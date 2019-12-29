#include "bgeigie_connector.h"
#include "debugger.h"
#include "identifiers.h"

BGeigieConnector::BGeigieConnector(Stream& serial_connection) :
    Worker<Reading>(k_worker_bgeigie_connector, Reading(), 4000),
    _serial_connection(serial_connection),
    _buffer("") {
}

int8_t BGeigieConnector::produce_data() {
  while(_serial_connection.available() > 0) {
    char c = static_cast<char>(_serial_connection.read());
    _buffer += c;
    if(c == '\n') {
      data = _buffer.c_str();
      _buffer = "";
      return data.get_status() & k_reading_parsed ? WorkerStatus::e_worker_data_read : WorkerStatus::e_worker_error;
    }
  }
  return WorkerStatus::e_worker_idle;
}

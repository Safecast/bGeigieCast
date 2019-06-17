#ifndef BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H
#define BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

#include <BLEDevice.h>
#include <StreamString.h>

#include <i_bluetooth_connector.h>

/**
 * Test class to inject in unit test controller
 */
class TestBluetoohConnector : public IBluetoohConnector {
 public:
  explicit TestBluetoohConnector(StreamString& output) : output(output) {}
  virtual ~TestBluetoohConnector() = default;

  void init(uint16_t device_id) override {
    // OK
  }

  void send_reading(Reading& reading) override {
    output.write((uint8_t*) reading.get_reading_str(), strlen(reading.get_reading_str()));
  }
 private:
  StreamString& output;

};

#endif //BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

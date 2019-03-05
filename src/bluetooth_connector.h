#ifndef BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H
#define BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

#include <BLEDevice.h>

class BluetoohConnector {
 public:
  BluetoohConnector();
  virtual ~BluetoohConnector() = default;

  void init();

  void send_reading(const char* reading, uint16_t size);
 private:
  void create_ble_profile_service(BLEServer* pServer);
  void create_ble_device_service(BLEServer* pServer);
  void create_ble_data_service(BLEServer* pServer);

  bool initialized;
  uint32_t temp_millis;

  uint8_t addr[6];
  uint32_t baud;

  uint8_t reading_final[2];
//  BLECharacteristic* pDataRXCharacteristic;

};

#endif //BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

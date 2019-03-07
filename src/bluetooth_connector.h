#ifndef BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H
#define BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

#include <BLEDevice.h>
#include "bluetooth_settings.h"

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
  uint8_t addr[6] = BLE_DATA_ADDR;
  uint8_t reading_final[2] = BLE_DATA_FINAL;
  BLECharacteristic* pDataRXCharacteristic;

};

#endif //BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

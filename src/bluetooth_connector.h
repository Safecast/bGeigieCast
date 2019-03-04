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
  bool initialized;
  uint32_t temp_millis;

  int addr = 0x0011223344;
  int baud = 0x00;

  BLECharacteristic* pProfileNameCharacteristic;
  BLECharacteristic* pProfileAppearanceCharacteristic;
  BLECharacteristic* pDeviceManufacturerCharacteristic;
  BLECharacteristic* pDeviceModelCharacteristic;
  BLECharacteristic* pDeviceFirmwareCharacteristic;
  BLECharacteristic* pDeviceRevisionCharacteristic;
  BLECharacteristic* pDataDBAddrCharacteristic;
  BLECharacteristic* pDataBaudCharacteristic;
  BLECharacteristic* pDataRXCharacteristic;
  BLECharacteristic* pDataTXCharacteristic;

};

#endif //BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

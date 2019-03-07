#ifndef BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H
#define BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

#include <BLEDevice.h>

#include "bluetooth_settings.h"
#include "reading.h"

/**
 * Setups up bluetooth endpoint for the device, allowing it to send readings over bluetooth
 */
class BluetoohConnector {
 public:
  BluetoohConnector();
  virtual ~BluetoohConnector() = default;

  /**
   * Initialize the bluetooth, using device id as name
   * @param device_id : id of the bgeigie device
   */
  void init(uint16_t device_id);

  /**
   * Send a new reading over bluetooth
   * @param reading : reading object to send
   */
  void send_reading(Reading& reading);
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

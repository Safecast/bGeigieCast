#ifndef BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H
#define BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H

#include <BLEDevice.h>

#include "i_bluetooth_connector.h"
#include "bluetooth_settings.h"
#include "../reading.h"

/**
 * Setups up bluetooth endpoint for the device, allowing it to send readings over bluetooth
 */
class BluetoohConnector : public IBluetoohConnector {
 public:
  BluetoohConnector();
  virtual ~BluetoohConnector() = default;

  /**
   * Initialize the bluetooth, using device id as name
   * @param device_id : id of the bgeigie device
   */
  void init(uint16_t device_id) override;

  /**
   * Send a new reading over bluetooth
   * @param reading : reading object to send
   */
  void send_reading(Reading& reading) override;
 private:
  void create_ble_profile_service(BLEServer* pServer);
  void create_ble_device_service(BLEServer* pServer);
  void create_ble_data_service(BLEServer* pServer);

  uint8_t addr[BLE_DATA_ADDR_SIZE] = BLE_DATA_ADDR;
  BLECharacteristic* pDataRXCharacteristic;

};

#endif //BGEIGIE_POINTCAST_BLUETOOTH_CONNECTOR_H
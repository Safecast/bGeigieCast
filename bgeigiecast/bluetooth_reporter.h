#ifndef BGEIGIECAST_BLUETOOTH_CONNECTOR_H
#define BGEIGIECAST_BLUETOOTH_CONNECTOR_H

#include <BLEDevice.h>

#include <Handler.hpp>

#include "bluetooth_settings.h"
#include "reading.h"
#include "local_storage.h"

/**
 * Setups up bluetooth endpoint for the device, allowing it to send readings over bluetooth
 */
class BluetoothReporter : public Handler {
 public:
  typedef enum Status {
    e_handler_idle = -1,
    e_handler_data_reported,
    e_handler_no_clients,
  } Status;

  explicit BluetoothReporter(LocalStorage& config);
  virtual ~BluetoothReporter() = default;

 protected:
  bool activate(bool retry) override;
  void deactivate() override;
  int8_t handle_produced_work(const worker_status_t& worker_reports) override;
 private:

  bool send_reading(const Reading& reading) const;

  void create_ble_profile_service(BLEServer* pServer);
  void create_ble_device_service(BLEServer* pServer);
  void create_ble_data_service(BLEServer* pServer);

  LocalStorage& config;
  BLEServer* pServer;
  BLECharacteristic* pDataRXCharacteristic;

  uint8_t addr[BLE_DATA_ADDR_SIZE] = BLE_DATA_ADDR;
};

#endif //BGEIGIECAST_BLUETOOTH_CONNECTOR_H

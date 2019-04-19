#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#include "bluetooth_connector.h"
#include "debugger.h"

BluetoohConnector::BluetoohConnector() : IBluetoohConnector() {
}

void BluetoohConnector::init(uint16_t device_id) {
  if(initialized) {
    return;
  }

  char deviceName[16];
  sprintf(deviceName, "bGeigie%d", device_id);

  BLEDevice::init(deviceName);
  BLEServer* pServer = BLEDevice::createServer();

  create_ble_profile_service(pServer);
  create_ble_device_service(pServer);
  create_ble_data_service(pServer);

  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_PROFILE_UUID);
  pAdvertising->addServiceUUID(SERVICE_DEVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_DATA_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);

  BLEDevice::startAdvertising();
  initialized = true;

  DEBUG_PRINT("Bluetooth initialized, device: "); DEBUG_PRINTLN(deviceName);
}

void BluetoohConnector::create_ble_profile_service(BLEServer* pServer) {
  if(initialized) {
    return;
  }
  BLEService* pProfileService = pServer->createService(SERVICE_PROFILE_UUID);
  BLECharacteristic* pProfileNameCharacteristic = pProfileService->createCharacteristic(
      CHARACTERISTIC_PROFILE_NAME_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  /*BLECharacteristic* pProfileAppearanceCharacteristic = */pProfileService->createCharacteristic(
      CHARACTERISTIC_PROFILE_APPEARANCE_UUID,
      BLECharacteristic::PROPERTY_READ
  );

  pProfileNameCharacteristic->setValue(BLE_PROFILE_NAME);

  pProfileService->start();
}

void BluetoohConnector::create_ble_device_service(BLEServer* pServer) {
  if(initialized) {
    return;
  }
  BLEService* pDeviceService = pServer->createService(SERVICE_DEVICE_UUID);

  // Manufacturer name
  BLECharacteristic* pDeviceManufacturerCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_MANUFACTURER_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEDescriptor* pDescriptorManufacturer = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorManufacturer->setValue("Manufacturer Name String");
  pDeviceManufacturerCharacteristic->addDescriptor(pDescriptorManufacturer);

  // Model number
  BLECharacteristic* pDeviceModelCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_MODEL_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEDescriptor* pDescriptorModel = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorModel->setValue("Model Number String");
  pDeviceModelCharacteristic->addDescriptor(pDescriptorModel);

  // Firmware revision
  BLECharacteristic* pDeviceFirmwareCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_FIRMWARE_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEDescriptor* pDescriptorFirmware = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorFirmware->setValue("Firmware Revision String");
  pDeviceFirmwareCharacteristic->addDescriptor(pDescriptorFirmware);

  // Hardware revision
  BLECharacteristic* pDeviceRevisionCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_REVISION_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEDescriptor* pDescriptorHardware = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorHardware->setValue("Hardware Revision String");
  pDeviceRevisionCharacteristic->addDescriptor(pDescriptorHardware);

  pDeviceManufacturerCharacteristic->setValue(BLE_DEVICE_INFO_MANUFACTURER);
  pDeviceModelCharacteristic->setValue(BLE_DEVICE_INFO_MODEL);
  pDeviceFirmwareCharacteristic->setValue(BLE_DEVICE_INFO_FIRMWARE_REVISION);
  pDeviceRevisionCharacteristic->setValue(BLE_DEVICE_INFO_HARDWARE_REVISION);

  pDeviceService->start();
}

void BluetoohConnector::create_ble_data_service(BLEServer* pServer) {
  if(initialized) {
    return;
  }
  BLEService* pDataService = pServer->createService(SERVICE_DATA_UUID);

  // DB Addr
  BLECharacteristic* pDataDBAddrCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_BDADDR_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEDescriptor* pDescriptorAddr = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorAddr->setValue("DB-Addr");
  pDataDBAddrCharacteristic->addDescriptor(pDescriptorAddr);

  // Baudrate
  BLECharacteristic* pDataBaudCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_BAUD_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );
  BLEDescriptor* pDescriptorBaud = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorBaud->setValue("Baudrate");
  pDataBaudCharacteristic->addDescriptor(pDescriptorBaud);

  // RX
  pDataRXCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_RX_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  BLEDescriptor* pDescriptorRX = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorRX->setValue("RX");
  pDataRXCharacteristic->addDescriptor(pDescriptorRX);
  BLEDescriptor* pDescriptorRXNotifications = new BLEDescriptor((uint16_t) 0x2902);
  pDescriptorRXNotifications->setValue("Notifications and indications disabled");
  pDataRXCharacteristic->addDescriptor(pDescriptorRXNotifications);

  // TX
  BLECharacteristic* pDataTXCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_TX_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );
  BLEDescriptor* pDescriptorTX = new BLEDescriptor((uint16_t) 0x2901);
  pDescriptorTX->setValue("TX");
  pDataTXCharacteristic->addDescriptor(pDescriptorTX);

  pDataDBAddrCharacteristic->setValue(addr, BLE_DATA_ADDR_SIZE);

  pDataService->start();
}

void BluetoohConnector::send_reading(Reading* reading) {
  if(!initialized) {
    init(reading->get_device_id());
  }
  DEBUG_PRINTLN("Sending reading over Bluetooth");
  const char* reading_str = reading->get_reading_str();
  size_t size = strlen(reading_str);

  int segment = 0;
  const static uint8_t max_segment_size = 20; // Max that can be send over bluetooth
  do {
    ++segment;
    uint8_t segment_size = segment * max_segment_size > size ? size % max_segment_size : max_segment_size;
    char to_send[segment_size];
    strncpy(to_send, reading_str + ((segment - 1) * max_segment_size), segment_size);

    pDataRXCharacteristic->setValue((uint8_t*) to_send, segment_size);
    pDataRXCharacteristic->notify();
  } while(segment * max_segment_size < size);
}

#include <Arduino.h>

#include "bluetooth_connector.h"
#include "bluetooth_settings.h"

BluetoohConnector::BluetoohConnector(): initialized(false), temp_millis(0) {
}

void BluetoohConnector::init() {

  BLEDevice::init("Safecast ESP32test");
  BLEServer* pServer = BLEDevice::createServer();

  BLEService* pProfileService = pServer->createService(SERVICE_PROFILE_UUID);
  pProfileNameCharacteristic = pProfileService->createCharacteristic(
      CHARACTERISTIC_PROFILE_NAME_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  pProfileAppearanceCharacteristic = pProfileService->createCharacteristic(
      CHARACTERISTIC_PROFILE_APPEARANCE_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEService* pDeviceService = pServer->createService(SERVICE_DEVICE_UUID);
  pDeviceManufacturerCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_MANUFACTURER_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  pDeviceModelCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_MODEL_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  pDeviceFirmwareCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_FIRMWARE_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  pDeviceRevisionCharacteristic = pDeviceService->createCharacteristic(
      CHARACTERISTIC_DEVICE_REVISION_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  BLEService* pDataService= pServer->createService(SERVICE_DATA_UUID);
  pDataDBAddrCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_BDADDR_UUID,
      BLECharacteristic::PROPERTY_READ
  );
  pDataBaudCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_BAUD_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );
  pDataRXCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_RX_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  pDataTXCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_DATA_TX_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );



  pProfileNameCharacteristic->setValue("bGeigie test");
  pDeviceManufacturerCharacteristic->setValue("Safecast");
  pDeviceModelCharacteristic->setValue("bGeigieNano ESP32");
  pDeviceFirmwareCharacteristic->setValue("1.0.0");
  pDeviceRevisionCharacteristic->setValue("1.0.0 REV-A");

  pProfileService->start();
  pDeviceService->start();
  pDataService->start();

  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_PROFILE_UUID);
  pAdvertising->addServiceUUID(SERVICE_DEVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_DATA_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);

  BLEDevice::startAdvertising();
  initialized = true;
}

void BluetoohConnector::send_reading(const char* reading, uint16_t size) {
  if(initialized && millis() > temp_millis + 5000) {
    pDataRXCharacteristic->setValue((uint8_t*) reading, size);
    temp_millis = millis();
  }
}

# 1 "/tmp/tmpvGeUDF"
#include <Arduino.h>
# 1 "/home/klei/Documents/HAN/Stage/Safecast/bGeigieCast/bGeigieCast/bgeigiecast/bgeigiecast.ino"
# 39 "/home/klei/Documents/HAN/Stage/Safecast/bGeigieCast/bGeigieCast/bgeigiecast/bgeigiecast.ino"
#ifndef UNIT_TEST

#include <Arduino.h>
#include "bluetooth_connector.h"
#include "api_connector.h"
#include "debugger.h"
#include "controller.h"

HardwareSerial& bGeigieSerialConnection = Serial2;
void controller_sleep(uint32_t millis_to_sleep);
void setup();
void loop();
#line 49 "/home/klei/Documents/HAN/Stage/Safecast/bGeigieCast/bGeigieCast/bgeigiecast/bgeigiecast.ino"
void controller_sleep(uint32_t millis_to_sleep) {
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  esp_sleep_enable_timer_wakeup(millis_to_sleep * 1000);

  DEBUG_PRINTLN("-----\nEntering sleep");
  DEBUG_FLUSH();
  esp_light_sleep_start();
  DEBUG_PRINTLN("Woke up from sleep\n-----");

  switch(esp_sleep_get_wakeup_cause()) {
    case ESP_SLEEP_WAKEUP_TIMER:
      break;
    case ESP_SLEEP_WAKEUP_GPIO:
      gpio_wakeup_disable((gpio_num_t) MODE_BUTTON_PIN);
      gpio_wakeup_enable((gpio_num_t) MODE_BUTTON_PIN, digitalRead(MODE_BUTTON_PIN) ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);
      break;
    default:
      break;
  }
}

EspConfig config;
ApiConnector api_conn(config);
BluetoohConnector bt_conn;

#if USE_SLEEP
Controller controller(config, bGeigieSerialConnection, api_conn, bt_conn, &controller_sleep);
#else
Controller controller(config, bGeigieSerialConnection, api_conn, bt_conn);
#endif

void setup() {
  DEBUG_BEGIN(SERIAL_BAUD);



  bGeigieSerialConnection.begin(BGEIGIE_CONNECTION_BAUD);


  gpio_config_t io_conf{
      .pin_bit_mask = 1ULL << MODE_BUTTON_PIN,
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&io_conf);
  gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);

  gpio_wakeup_enable((gpio_num_t) MODE_BUTTON_PIN, GPIO_INTR_LOW_LEVEL);


  esp_sleep_enable_gpio_wakeup();



  controller.setup_state_machine();
}

void loop() {
  controller.run();
}

#endif
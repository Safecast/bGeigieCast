/* bGeigieCast is an addon for bGeigieNano to be used as a fixed sensor device. Hardware is a Xbee socket
 * with ESP32 and some extra components on it.
 *
 * wiki: https://github.com/Safecast/bGeigieCast/wiki
 *
 *  Copyright (c) 2019, Safecast

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


History Versions:

Contact: Jelle Bouwhuis (email jellebouwhuis@outlook.com) and Rob Oudendijk (rob@yr-design.biz)

 */


#include <Arduino.h>
#include "bluetooth_connector.h"
#include "api_connector.h"
#include "debugger.h"
#include "controller.h"

#ifndef UNIT_TEST

HardwareSerial& bGeigieSerialConnection = Serial2;

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

  /// Hardware configurations
  // Start serial connection to bGeigie controller
  bGeigieSerialConnection.begin(BGEIGIE_CONNECTION_BAUD);

  // Set gpio pin configurations
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

  // Set sleep options
  esp_sleep_enable_gpio_wakeup();

  /// Software configurations
  // Setup controller
  controller.setup_state_machine();
}

void loop() {
  controller.run();
}

#endif

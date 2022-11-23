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

#ifndef UNIT_TEST

#include <Arduino.h>

#include "bluetooth_reporter.h"
#include "api_connector.h"
#include "access_point.h"
#include "debugger.h"
#include "controller.h"
#include "bgeigie_connector.h"
#include "configuration_server.h"
#include "mode_led.h"

HardwareSerial& bGeigieSerialConnection = Serial2;

LocalStorage config;
Controller controller(config);

// Workers
BGeigieConnector bgeigie_connector(bGeigieSerialConnection);
ConfigWebServer config_server(config);

// Data handlers
BluetoothReporter bluetooth_reporter(config);
ApiReporter api_reporter(config);
AccessPoint access_point(config);

// Report handlers
ModeLED mode_led(config);

#if DEBUG_FULL_REPORT
#if ENABLE_DEBUG
#include "identifiers.h"

/**
 * Prints full details of the workers and handlers
 */
class FullReporter : public Supervisor {
  void handle_report(const Report& report) override {
    auto& worker_stats = report.get_worker_stats();
    auto& handler_stats = report.get_handler_stats();
    DEBUG_PRINTF(
        "Workers:\n"
        "- bgeigie_connector\n"
        "  - state: %d, status: %d\n"
        "- configuration_server\n"
        "  - state: %d, status: %d\n"
        "Handlers:\n"
        "- controller_handler\n"
        "  - state: %d, status: %d\n"
        "- storage_handler\n"
        "  - state: %d, status: %d\n"
        "- bluetooth_reporter\n"
        "  - state: %d, status: %d\n"
        "- api_reporter\n"
        "  - state: %d, status: %d\n",
        worker_stats.at(k_worker_bgeigie_connector).active_state,
        worker_stats.at(k_worker_bgeigie_connector).status,
        worker_stats.at(k_worker_configuration_server).active_state,
        worker_stats.at(k_worker_configuration_server).status,
        handler_stats.at(k_handler_controller_handler).active_state,
        handler_stats.at(k_handler_controller_handler).status,
        handler_stats.at(k_handler_storage_handler).active_state,
        handler_stats.at(k_handler_storage_handler).status,
        handler_stats.at(k_handler_bluetooth_reporter).active_state,
        handler_stats.at(k_handler_bluetooth_reporter).status,
        handler_stats.at(k_handler_api_reporter).active_state,
        handler_stats.at(k_handler_api_reporter).status
    );
  }
};
FullReporter full_reporter;

#endif
#endif

void setup() {
  DEBUG_BEGIN(SERIAL_BAUD);

  /// Hardware configurations
  // Start serial connection to bGeigie controller
  bGeigieSerialConnection.begin(BGEIGIE_CONNECTION_BAUD);

  // Set gpio pin configurations
  gpio_config_t io_conf{
      .pin_bit_mask = 1ULL<<MODE_BUTTON_PIN,
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&io_conf);
  gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);

  /// Software configurations
  // Setup aggregator
  controller.register_worker(access_point, false);
  controller.register_worker(bgeigie_connector, false);
  controller.register_worker(config_server, false);

  controller.register_handler(bluetooth_reporter, false);
  controller.register_handler(api_reporter, false);
  controller.register_handler(config, false);

  controller.register_supervisor(mode_led);
#if DEBUG_FULL_REPORT
#if ENABLE_DEBUG
  controller.register_supervisor(full_reporter);
#endif
#endif
  controller.setup_state_machine();
}

void loop() {
  controller.run();
  mode_led.loop();
}

#endif

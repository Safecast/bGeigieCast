#include <Arduino.h>
#include <StreamString.h>
#include <unity.h>

#include <controller.h>
#include <state_machine/states/active_states/stationary_mode_states/ConnectionErrorState.h>

#include "../test_config.h"
#include "../test_bluetooth.h"
#include "../test_api.h"


/**
 * Test saving 10000 failed readings
 */
void test_readings_saving() {
  StreamString bgeigie_connection;
  StreamString api_output;
  StreamString bt_output;
  TestEspConfig config;
  TestApiConnector api_conn(config, api_output);
  TestBluetoohConnector bt_conn(bt_output);
  Controller controller(config, bgeigie_connection, api_conn, bt_conn);

  controller.set_state(new ConnectionErrorState(controller));

  const uint32_t heap_before_new = ESP.getFreeHeap();
  Reading* readingP = new Reading();

  TEST_ASSERT_LESS_OR_EQUAL(heap_before_new - sizeof(Reading), ESP.getFreeHeap());

  delete readingP;

  const char* some_reading = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46\r\n";

  const uint32_t initial_heap = ESP.getFreeHeap();

  for(int i = 0; i < 3; ++i) {
    bgeigie_connection += some_reading;
    controller.run();
    // Clear bt buffer
    while(bt_output.available()) {bt_output.read();}
  }

  const uint32_t heap_after = ESP.getFreeHeap();

  TEST_ASSERT_LESS_OR_EQUAL(initial_heap - (sizeof(Reading) * 3), heap_after);

  for(int i = 0; i < 10000; ++i) {
    bgeigie_connection += some_reading;
    controller.run();
    // Clear bt buffer
    while(bt_output.available()) {bt_output.read();}
  }

  uint32_t current_heap = ESP.getFreeHeap();
  TEST_ASSERT_LESS_OR_EQUAL(heap_after + 4, current_heap);
  TEST_ASSERT_GREATER_OR_EQUAL(heap_after - 4, current_heap);
}

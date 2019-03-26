#include <Arduino.h>
#include <StreamString.h>
#include <unity.h>

#include <controller.h>
#include <state_machine/states/active_states/stationary_mode_states/ConnectionErrorState.h>

#include "../test_config.h"

/**
 * To set the millis
 * @param ms
 */
void setMillis(unsigned long ms)
{
}

/**
 * Test saving 1000000 failed readings
 */
void test_readings_saving() {


  set_millis_fn(fn);


  // Init
  TestEspConfig config;
  StreamString bgeigie_connection;
  config.set_init_stationary(true, false);
  Controller controller(config, bgeigie_connection);

  controller.set_state(new ConnectionErrorState(controller));

  const uint32_t heap_before_new = ESP.getFreeHeap();
  Reading* readingP = new Reading();

  TEST_ASSERT_LESS_OR_EQUAL(heap_before_new - sizeof(Reading), ESP.getFreeHeap());

  delete readingP;

  const char* some_reading = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46\r\n";

  const uint32_t initial_heap = ESP.getFreeHeap();

  for(int i = 0; i < 3; ++i) {
    setMillis(millis() + (API_SEND_FREQUENCY_MINUTES * 60 * 1000) + 1);
    bgeigie_connection += some_reading;
    controller.process_possible_bgeigie_readings(false, true); // Report to API (which is not connected)
  }

  const uint32_t heap_after = ESP.getFreeHeap();

  TEST_ASSERT_LESS_OR_EQUAL(initial_heap - (sizeof(Reading) * 3), heap_after);

  for(int i = 0; i < 100000; ++i) {
    setMillis(millis() + (API_SEND_FREQUENCY_MINUTES * 60 * 1000) + 1);
    bgeigie_connection += some_reading;
    controller.process_possible_bgeigie_readings(false, true); // Report to API (which is not connected)
  }

  uint32_t current_heap = ESP.getFreeHeap();
  TEST_ASSERT_LESS_OR_EQUAL(heap_after + 4, current_heap);
  TEST_ASSERT_GREATER_OR_EQUAL(heap_after - 4, current_heap);
}

#include <unity.h>
#include <Arduino.h>
#include <StreamString.h>
#include <controller.h>
#include <state_machine/states/InitializeState.h>
#include <state_machine/states/PostInitializeState.h>

#include "../test_config.h"

/**
 * Test controller initial state transition
 */
void controller_init(void) {
  TestEspConfig config;
  StreamString bgeigie_connection;
  Controller controller(config, bgeigie_connection);

  TEST_ASSERT_EQUAL(controller.get_current_state(), nullptr);

  controller.setup_state_machine();

  TEST_ASSERT_NOT_NULL(dynamic_cast<InitializeState*>(controller.get_current_state()));

  controller.run();

  TEST_ASSERT_NOT_NULL(dynamic_cast<PostInitializeState*>(controller.get_current_state()));
}

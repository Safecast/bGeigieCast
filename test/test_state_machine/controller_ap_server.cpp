#include <unity.h>
#include <controller.h>
#include <state_machine/states/InitializeState.h>
#include <state_machine/states/active_states/MobileModeState.h>

/**
 * Test controller state transition to start AP server
 */
void controller_ap_server(void) {
  Controller controller;

  TEST_ASSERT_EQUAL(controller.get_current_state(), nullptr);

  controller.setup_state_machine();

  TEST_ASSERT_NOT_NULL(dynamic_cast<InitializeState*>(controller.get_current_state()));

  controller.run();

  TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));
}
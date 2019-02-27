#include <Arduino.h>
#include <unity.h>
#include <controller.h>
#include <state_machine/states/SetupServerState.hpp>

/**
 * Test controller state transition to start AP server
 */
void controller_ap_server(void) {
  Controller controller;

  controller.set_state(new SetupServerState(controller));

  TEST_ASSERT_NOT_NULL(dynamic_cast<InitializeState*>(controller.get_current_state()));

  controller.run();

  TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));
}

#include <Arduino.h>
#include <unity.h>
#include <controller.h>
#include <state_machine/states/InitializeState.h>
#include <state_machine/states/PostInitializeState.h>
#include <state_machine/states/SetupServerState.hpp>
#include <state_machine/states/ServerActiveState.hpp>
#include <state_machine/states/active_states/MobileModeState.h>
#include <state_machine/states/active_states/StationaryModeState.h>
#include <state_machine/states/active_states/stationary_mode_states/ConnectionErrorState.h>
#include <state_machine/states/active_states/stationary_mode_states/ConnectingState.h>
#include <state_machine/states/active_states/stationary_mode_states/ConnectedState.h>
#include <state_machine/states/active_states/stationary_mode_states/TestApiState.h>

/**
 * Test controller state transition: Init -> MobileMode
 */
void controller_state_transitions_init_mobile(void) {
  // Init -> MobileMode
  Controller controller;
  controller.setup_state_machine();

  TEST_ASSERT_NOT_NULL(dynamic_cast<InitializeState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_controller_initialized);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<PostInitializeState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_post_init_time_passed);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));
}

/**
 * Test controller state transition: Init -> SetupServer
 */
void controller_state_transitions_init_server(void) {
  // Init -> SetupServer -> ServerActive
  Controller controller;
  controller.setup_state_machine();

  TEST_ASSERT_NOT_NULL(dynamic_cast<InitializeState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_controller_initialized);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<PostInitializeState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_button_pressed);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<SetupServerState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_server_initialized);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<ServerActiveState*>(controller.get_current_state()));
}

/**
 * Test controller state transition: MobileMode -> StationaryMode
 */
void controller_state_transitions_mobile_stationary(void) {
  // MobileMode -> StationaryMode -> MobileMode
  Controller controller;
  controller.set_state(new MobileModeState(controller));

  TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_button_pressed);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<StationaryModeState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_button_pressed);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));
}

/**
 * Test controller state transition: Connecting -> ApiTest
 */
void controller_state_transitions_connecting_test_connected(void) {
  // Connecting -> ApiTest -> Connected
  Controller controller;
  controller.set_state(new ConnectingState(controller));

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectingState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_connected);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<TestApiState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_API_available);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectedState*>(controller.get_current_state()));
}

/**
 * Test controller state transition: Connecting -> ConnectionError
 */
void controller_state_transitions_connecting_error_connected(void) {
  // Connecting -> ConnectionError -> ApiTest -> Connected
  Controller controller;
  controller.set_state(new ConnectingState(controller));

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectingState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_connection_failed);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectionErrorState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_connected);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<TestApiState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_API_available);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectedState*>(controller.get_current_state()));
}

/**
 * Test controller state transition: Connected -> ConnectionError
 */
void controller_state_transitions_connected_error(void) {
  // Connected -> ConnectionError
  Controller controller;
  controller.set_state(new ConnectedState(controller));

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectedState*>(controller.get_current_state()));

  controller.schedule_event(Event_enum::e_connection_lost);
  controller.handle_events();

  TEST_ASSERT_NOT_NULL(dynamic_cast<ConnectionErrorState*>(controller.get_current_state()));
}

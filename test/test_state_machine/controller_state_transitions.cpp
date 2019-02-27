#include <Arduino.h>
#include <unity.h>
#include <controller.h>
#include <state_machine/states/InitializeState.h>
#include <state_machine/states/SetupServerState.hpp>
#include <state_machine/states/ServerActiveState.hpp>
#include <state_machine/states/active_states/MobileModeState.h>
#include <state_machine/states/active_states/StationaryModeState.h>

/**
 * Test controller state transition to start AP server
 */
void controller_state_transitions(void) {
  {
    // Init -> MobileMode
    Controller controller;

    controller.set_state(new InitializeState(controller));

    controller.schedule_event(Event_enum::e_controller_initialized);
    controller.handle_events();

    TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));
  }
  {
    // Init -> SetupServer -> ServerActive
    Controller controller;

    controller.set_state(new InitializeState(controller));

    controller.get_mode_button().state_changed(HIGH);

    controller.schedule_event(Event_enum::e_controller_initialized);
    controller.handle_events();

    TEST_ASSERT_NOT_NULL(dynamic_cast<SetupServerState*>(controller.get_current_state()));

    controller.schedule_event(Event_enum::e_server_initialized);
    controller.handle_events();

    TEST_ASSERT_NOT_NULL(dynamic_cast<ServerActiveState*>(controller.get_current_state()));
  }
  {
    // MobileMode -> StationaryMode -> MobileMode
    Controller controller;

    controller.set_state(new MobileModeState(controller));

    controller.schedule_event(Event_enum::e_button_pressed);
    controller.handle_events();

    TEST_ASSERT_NOT_NULL(dynamic_cast<StationaryModeState*>(controller.get_current_state()));

    controller.schedule_event(Event_enum::e_button_pressed);
    controller.handle_events();

    TEST_ASSERT_NOT_NULL(dynamic_cast<MobileModeState*>(controller.get_current_state()));
  }
}

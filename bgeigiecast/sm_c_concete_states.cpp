#include <Aggregator.hpp>

#include "sm_c_concete_states.h"
#include "identifiers.h"

// region InitializeState

InitializeState::InitializeState(Controller& context) : ControllerState(context) {
}

void InitializeState::entry_action() {
  DEBUG_PRINTLN("-- Entered state Initialize");
}

void InitializeState::do_activity() {
  controller.initialize();
}

void InitializeState::exit_action() {

}

void InitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_controller_initialized: {
      controller.set_state(new InitReadingState(controller));
      break;
    }
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region InitReadingState

InitReadingState::InitReadingState(Controller& context) : ControllerState(context) {
}

void InitReadingState::entry_action() {
  DEBUG_PRINTLN("-- Entered state Initialize reading");
}

void InitReadingState::do_activity() {
}

void InitReadingState::exit_action() {

}

void InitReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_reading_initialized: {
      controller.set_state(new PostInitializeState(controller));
      break;
    }
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region PostInitializeState

PostInitializeState::PostInitializeState(Controller& context) : ControllerState(context), timer(0) {
}

void PostInitializeState::entry_action() {
  DEBUG_PRINTLN("-- Entered state PostInitialize");
  timer = millis();
}

void PostInitializeState::do_activity() {
  if(millis() - timer > POST_INITIALIZE_DURATION) {
    controller.schedule_event(e_c_post_init_time_passed);
  }
}

void PostInitializeState::exit_action() {
}

void PostInitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new ConfigurationModeState(controller));
      break;
    case e_c_post_init_time_passed: {
      switch(controller.get_saved_state()) {
        case Controller::k_savable_FixedMode:
          controller.set_state(new FixedModeState(controller));
          break;
        case Controller::k_savable_MobileMode:
        default:
          controller.set_state(new MobileModeState(controller));
          break;
      }
      break;
    }
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region ConfigModeState

ConfigurationModeState::ConfigurationModeState(Controller& context) : ControllerState(context) {
}

void ConfigurationModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

void ConfigurationModeState::entry_action() {
//  controller.set_worker_active(k_worker_configuration_server, true);
}

void ConfigurationModeState::do_activity() {

}

void ConfigurationModeState::exit_action() {
//  controller.set_worker_active(k_worker_configuration_server, true);
}

// endregion

// region MobileModeState

MobileModeState::MobileModeState(Controller& context) : ControllerState(context) {
}

void MobileModeState::entry_action() {
  DEBUG_PRINTLN("-- Entered state MobileMode");
  controller.save_state(Controller::k_savable_MobileMode);
//  controller.set_handler_active(k_handler_bluetooth_reporter, true);
}

void MobileModeState::do_activity() {
}

void MobileModeState::exit_action() {
//  controller.set_handler_active(k_handler_bluetooth_reporter, false);
}

void MobileModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new FixedModeState(controller));
      break;
    case e_c_report_success:
      // Success, no need to do anything
      break;
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}


// endregion

// region FixedModeState

FixedModeState::FixedModeState(Controller& context) : ControllerState(context) {
}

void FixedModeState::entry_action() {

}

void FixedModeState::do_activity() {
}

void FixedModeState::exit_action() {

}

void FixedModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new MobileModeState(controller));
      break;
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region ResetState

ResetState::ResetState(Controller& context) : ControllerState(context) {

}

void ResetState::entry_action() {
  DEBUG_PRINTLN("-- Entered state Reset");
}

void ResetState::do_activity() {
  controller.reset_system();
}

void ResetState::exit_action() {

}

void ResetState::handle_event(Event_enum event_id) {
  ControllerState::handle_event(event_id);
}

// endregion

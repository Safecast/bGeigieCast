#include "sm_c_concete_states.h"

// region InitializeState

InitializeState::InitializeState(Controller& context) : ControllerState(context) {
}

void InitializeState::entry_action() {
  DEBUG_PRINTLN("-- Entered state Initialize");
  controller._mode_led.set_color(ModeLED::ModeColor::init);
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

#define BLINK_FREQUENCY 1
#define BLINK_DURATION_PERCENTAGE 10

InitReadingState::InitReadingState(Controller& context) : ControllerState(context) {
}

void InitReadingState::entry_action() {
  DEBUG_PRINTLN("-- Entered state Initialize reading");
  controller._mode_led.set_color(ModeLED::ModeColor::init);
}

void InitReadingState::do_activity() {
  controller._mode_led.blink(ModeLED::ModeColor::init, BLINK_FREQUENCY, BLINK_DURATION_PERCENTAGE);
  controller._reporter.run();
  if(controller._reporter.get_last_reading()) {
    controller.schedule_event(e_c_reading_initialized);
  }
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

#define POST_INIT_DURATION_MILLIS 3000

PostInitializeState::PostInitializeState(Controller& context) : ControllerState(context), timer(0) {
}

void PostInitializeState::entry_action() {
  DEBUG_PRINTLN("-- Entered state PostInitialize");
  controller._mode_led.set_color(ModeLED::ModeColor::init);
  timer = millis();
}

void PostInitializeState::do_activity() {
  if(millis() - timer > POST_INIT_DURATION_MILLIS) {
    controller.schedule_event(e_c_post_init_time_passed);
  }
}

void PostInitializeState::exit_action() {
}

void PostInitializeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new SetupServerState(controller));
      break;
    case e_c_post_init_time_passed:
      controller.set_state(new InitActiveState(controller));
      break;
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region ConfigModeState

ConfigModeState::ConfigModeState(Controller& context): ControllerState(context) {
}

void ConfigModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region SetupServerState

SetupServerState::SetupServerState(Controller& context) : ConfigModeState(context) {
}

void SetupServerState::entry_action() {
  DEBUG_PRINTLN("-- Entered state SetupServer");
  controller._mode_led.set_color(ModeLED::ModeColor::init_config);
}

void SetupServerState::do_activity() {
  if(controller._ap_server.initialize()) {
    controller.schedule_event(Event_enum::e_c_server_initialized);
  }
}

void SetupServerState::exit_action() {
}

void SetupServerState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_server_initialized:
      controller.set_state(new ServerActiveState(controller));
      break;
    default:
      ConfigModeState::handle_event(event_id);
      break;
  }
}

// endregion

// region ServerActiveState

ServerActiveState::ServerActiveState(Controller& context) : ConfigModeState(context) {
}

void ServerActiveState::entry_action() {
  DEBUG_PRINTLN("-- Entered state ServerActive");
  controller._mode_led.set_color(ModeLED::ModeColor::config);
}

void ServerActiveState::do_activity() {
  controller._ap_server.handle_requests();
}

void ServerActiveState::exit_action() {
  controller._ap_server.stop();
}

void ServerActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new InitActiveState(controller));
      break;
    default:
      ConfigModeState::handle_event(event_id);
      break;
  }
}

// endregion

// region ActiveState

ActiveState::ActiveState(Controller& context): ControllerState(context) {
}

void ActiveState::do_activity() {
  controller.sleep();
}

void ActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_long_pressed:
      controller.set_state(new ResetState(controller));
      break;
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

// endregion

// region InitActiveState

InitActiveState::InitActiveState(Controller& context) : ActiveState(context) {
}

void InitActiveState::entry_action() {
  DEBUG_PRINTLN("-- Entered state ActiveInit");
}

void InitActiveState::do_activity() {
  switch(controller.get_saved_state()) {
    case k_savable_FixedMode:
      controller.set_state(new DisconnectedState(controller));
      break;
    case k_savable_MobileMode:
    default:
      controller.set_state(new MobileModeState(controller));
      break;
  }
}

void InitActiveState::exit_action() {

}

void InitActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

// endregion

// region MobileModeState

MobileModeState::MobileModeState(Controller& context): ActiveState(context) {
}

void MobileModeState::entry_action() {
  DEBUG_PRINTLN("-- Entered state MobileMode");
  controller.save_state(k_savable_MobileMode);
  controller._mode_led.set_color(ModeLED::ModeColor::mobile);
  controller.set_reporter_outputs(true, false);
}

void MobileModeState::do_activity() {
  ActiveState::do_activity();
}

void MobileModeState::exit_action() {
}

void MobileModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new DisconnectedState(controller));
      break;
    case e_c_report_success:
      // Success, no need to do anything
      break;
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}


// endregion

// region FixedModeState

FixedModeState::FixedModeState(Controller& context) : ActiveState(context) {
}

void FixedModeState::do_activity() {
  ActiveState::do_activity();
}

void FixedModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_button_pressed:
      controller.set_state(new MobileModeState(controller));
      break;
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

// endregion

// region DisconnectedState

DisconnectedState::DisconnectedState(Controller& context): FixedModeState(context), state_entry_moment(0) {
}

void DisconnectedState::entry_action() {
  DEBUG_PRINTLN("-- Entered state FixedMode, Disconnected");
  controller.save_state(k_savable_FixedMode);
  controller._mode_led.set_color(ModeLED::ModeColor::fixed_connecting);
  controller.set_reporter_outputs(true, true);
}

void DisconnectedState::do_activity() {
  FixedModeState::do_activity();
}

void DisconnectedState::exit_action() {
}

void DisconnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_report_success:
      controller.set_state(new ConnectedState(controller));
      break;
    case e_c_report_failed:
      controller.set_state(new ConnectionErrorState(controller));
      break;
    default:
      FixedModeState::handle_event(event_id);
      break;
  }
}

// endregion

// region ConnectedState

ConnectedState::ConnectedState(Controller& context): FixedModeState(context) {
}

void ConnectedState::entry_action() {
  DEBUG_PRINTLN("-- Entered state Connected");
  controller._mode_led.set_color(ModeLED::ModeColor::fixed_active);
}

void ConnectedState::do_activity() {
  FixedModeState::do_activity();
}

void ConnectedState::exit_action() {
}

void ConnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_report_failed:
      controller.set_state(new DisconnectedState(controller));
      break;
    case e_c_report_success:
      // Success, no need to do anything already in connected state
      break;
    default:
      FixedModeState::handle_event(event_id);
      break;
  }
}

// endregion

// region ConnectionErrorState

ConnectionErrorState::ConnectionErrorState(Controller& context) : FixedModeState(context), timer(0){
}

void ConnectionErrorState::entry_action() {
  DEBUG_PRINTLN("-- Entered state ConnectionError");
  controller._mode_led.set_color(ModeLED::ModeColor::fixed_error);
  timer = millis();
}

void ConnectionErrorState::do_activity() {
  FixedModeState::do_activity();
}

void ConnectionErrorState::exit_action() {
}

void ConnectionErrorState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_report_success:
      controller.set_state(new ConnectedState(controller));
      break;
    case e_c_report_failed:
      // Failed, Nothing happening already in connection error state
      break;
    default:
      FixedModeState::handle_event(event_id);
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

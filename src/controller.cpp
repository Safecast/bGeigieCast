#include "state_machine/states/InitializeState.h"
#include "state_machine/states/active_states/MobileModeState.h"
#include "state_machine/states/active_states/StationaryModeState.h"
#include "controller.h"
#include "reading.h"


Controller::Controller(IEspConfig& config, Stream& bGegie_connection_stream) :
    Context(),
    ButtonObserver(),
    _config(config),
    _ap_server(config),
    _api_connector(config),
    _mode_button(MODE_BUTTON_PIN),
    _state_led(),
    _bluetooth(),
    _bgeigie_connector(bGegie_connection_stream) {
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
}

void Controller::set_state(AbstractState* state) {
  Context::set_state(state);
  if(dynamic_cast<StationaryModeState*>(state)) {
    _config.set_init_stationary(true, false);
  }
  else if(dynamic_cast<MobileModeState*>(state)) {
    _config.set_init_stationary(false, false);
  }
}

void Controller::initialize() {
  _mode_button.set_observer(this);
  _config.set_all();

  schedule_event(Event_enum::e_controller_initialized);
}

void Controller::on_button_pressed(Button* button, uint32_t millis_pressed) {
  if(button->get_pin() == MODE_BUTTON_PIN) {
    if(millis_pressed > 4000) {
      schedule_event(Event_enum::e_button_long_pressed);
    } else {
      schedule_event(Event_enum::e_button_pressed);
    }
  }
}

void Controller::process_possible_bgeigie_readings(bool report_bluetooth, bool report_api) {
  Reading* reading = nullptr;

  if(_bgeigie_connector.get_reading(&reading) && reading && reading->correctly_parsed()) {
    if(report_bluetooth) {
      _bluetooth.send_reading(*reading);
    }
    if(report_api) {
      _api_connector.process_reading(*reading);
    }
  }
  delete reading;
}

IEspConfig& Controller::get_config() {
  return _config;
}

ConfigWebServer& Controller::get_ap_server() {
  return _ap_server;
}

ApiConnector& Controller::get_api_connector() {
  return _api_connector;
}

Button& Controller::get_mode_button() {
  return _mode_button;
}

StateLED& Controller::get_state_led() {
  return _state_led;
}

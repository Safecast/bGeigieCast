#include "state_machine/states/InitializeState.h"
#include "controller.h"
#include "reading.h"

Controller::Controller() :
    Context(),
    ButtonObserver(),
    _config(),
    _ap_server(_config),
    _api_connector(_config),
    _mode_button(MODE_BUTTON_PIN),
    _bluetooth(),
    _bgeigie_connector(Serial2){
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
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

  if(_bgeigie_connector.get_reading(&reading) && reading) {
    if(report_bluetooth) {
      _bluetooth.send_reading(*reading);
    }
    if(report_api) {
      _api_connector.process_reading(*reading);
    }
  }
  delete reading;
}

EspConfig& Controller::get_config() {
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

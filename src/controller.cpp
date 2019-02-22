#include "state_machine/states/InitializeState.h"
#include "controller.h"

Controller::Controller() : Context(), ButtonObserver(), _config(), _ap_server(_config), _mode_button(MODE_BUTTON_PIN) {
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
}

void Controller::initialize() {
  _mode_button.set_observer(this);
  _config.set_all();
  schedue_event(Event_enum::e_controller_initialized);
}

void Controller::on_button_pressed(Button* button, uint32_t millis) {
  if(button->get_pin() == MODE_BUTTON_PIN) {
    schedue_event(Event_enum::e_button_pressed);
  }
}

EspConfig& Controller::get_config() {
  return _config;
}

WebServer& Controller::get_ap_server() {
  return _ap_server;
}

void Controller::initialize_ap_server() {
  if(_ap_server.initialize()) {
    schedue_event(Event_enum::e_server_initialized);
  }
}

const Button& Controller::get_mode_button() const {
  return _mode_button;
}

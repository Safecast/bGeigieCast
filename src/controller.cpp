#include "state_machine/states/InitializeState.h"
#include "controller.h"

Controller::Controller() : _config(), _ap_server(_config) {
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
}

void Controller::initialize() {
  _config.set_all();
  schedue_event(Event_enum::e_controller_initialized);
}

void Controller::button_pressed_cb() {
  schedue_event(Event_enum::e_button_pressed);
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

#include "state_machine/sm_c_init.h"
#include "controller.h"
#include "reading.h"


Controller::Controller(IEspConfig& config, Stream& bGegie_connection_stream, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector, sleep_fn_t sleep_fn) :
    Context(),
    ButtonObserver(),
    _config(config),
    _reporter(config, bGegie_connection_stream, api_connector, bluetooth_connector),
    _ap_server(config),
    _mode_button(MODE_BUTTON_PIN),
    _state_led(config),
    _sleep_fn(sleep_fn){
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
}

void Controller::initialize() {
  _mode_button.activate();
  _mode_button.set_observer(this);
  _config.set_all();
  _reporter.setup_state_machine();

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

void Controller::run_reporter() {
//  _reporter.run();
//  _reporter.process_possible_bgeigie_readings(report_bluetooth, report_api);
}

void Controller::sleep() {
  if(_sleep_fn) {
    _sleep_fn(this);
  }
}

void Controller::reset_system() {
  _config.reset_defaults();
  DEBUG_PRINTLN("\n RESTARTING ESP...\n");
  ESP.restart();
}

void Controller::save_state(SavableState state) {
  _config.set_saved_state(state, false);
}

SavableState Controller::get_saved_state() {
  return static_cast<SavableState>(_config.get_saved_state());
}

ConfigWebServer& Controller::get_ap_server() {
  return _ap_server;
}

StateLED& Controller::get_state_led() {
  return _state_led;
}

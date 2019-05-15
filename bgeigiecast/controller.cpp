#include "sm_c_concete_states.h"
#include "controller.h"
#include "reading.h"

#define BUTTON_LONG_PRESSED_MILLIS_TRESHOLD 4000

Controller::Controller(IEspConfig& config,
                       Stream& bgeigie_connection,
                       IApiConnector& api_connector,
                       IBluetoohConnector& bluetooth_connector,
                       sleep_fn_t sleep_fn) :
    Context(),
    ButtonObserver(),
    _config(config),
    _reporter(config, bgeigie_connection, api_connector, bluetooth_connector),
    _ap_server(config),
    _mode_button(MODE_BUTTON_PIN),
    _mode_led(config),
    _sleep_fn(sleep_fn) {
  _reporter.set_observer(this);
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
}

void Controller::run() {
  Context::run();
  _reporter.run();
}

void Controller::initialize() {
  _mode_button.activate();
  _mode_button.set_observer(this);
  _config.set_all();
  _reporter.setup_state_machine();

  schedule_event(Event_enum::e_c_controller_initialized);
}

void Controller::on_button_pressed(Button* button, uint32_t millis_pressed) {
  if(button->get_pin() == MODE_BUTTON_PIN) {
    if(millis_pressed > BUTTON_LONG_PRESSED_MILLIS_TRESHOLD) {
//      DEBUG_PRINTLN("Button long pressed");
      schedule_event(Event_enum::e_c_button_long_pressed);
    } else {
//      DEBUG_PRINTLN("Button pressed");
      schedule_event(Event_enum::e_c_button_pressed);
    }
  }
}

void Controller::set_reporter_outputs(bool bt, bool api) {
  _reporter.set_report_output(bt, api);
}

void Controller::sleep() {
  if(_sleep_fn && _reporter.is_idle()) {
    uint32_t till_next = _reporter.time_till_next_reading(millis());
    if(till_next > 0) {
      _sleep_fn(till_next);
    }
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

void Controller::reading_reported(Reporter::ReporterStatus status) {
  switch(status) {
    case Reporter::k_reporter_failed:
      schedule_event(e_c_report_failed);
      break;
    case Reporter::k_reporter_success:
      schedule_event(e_c_report_success);
      break;
    case Reporter::k_reporter_no_change:
      // No change
      break;
  }
}

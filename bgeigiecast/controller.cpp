#include "sm_c_concete_states.h"
#include "controller.h"
#include "identifiers.h"

#define BUTTON_LONG_PRESSED_MILLIS_TRESHOLD 4000

Controller::Controller(LocalStorage& config) :
    ButtonObserver(),
    Context(),
    Aggregator(),
    Handler(k_handler_controller_handler),
    Worker<bool>(k_worker_controller_state_changer, false, 0),
    _config(config),
    _mode_button(MODE_BUTTON_PIN),
    _state_changed(false) {
}

void Controller::setup_state_machine() {
  set_state(new InitializeState(*this));
}

void Controller::run() {
  Context::run();
  Aggregator::run();
}

void Controller::initialize() {
  _mode_button.activate();
  _mode_button.set_observer(this);

  register_handler(*this, true);
  register_worker(*this, true);
  set_handler_active(k_handler_storage_handler, true);
  set_worker_active(k_worker_bgeigie_connector, true);

  schedule_event(Event_enum::e_c_controller_initialized);
}

void Controller::on_button_pressed(Button* button, uint32_t millis_pressed) {
  if(button->get_pin() == MODE_BUTTON_PIN) {
    if(millis_pressed > BUTTON_LONG_PRESSED_MILLIS_TRESHOLD) {
      DEBUG_PRINTLN("Button long pressed");
      schedule_event(Event_enum::e_c_button_long_pressed);
    } else {
      DEBUG_PRINTLN("Button pressed");
      schedule_event(Event_enum::e_c_button_pressed);
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

Controller::SavableState Controller::get_saved_state() {
  return static_cast<SavableState>(_config.get_saved_state());
}

int8_t Controller::handle_produced_work(const worker_status_t& worker_reports) {
  auto current_state = get_current_state()->get_state_id();
  if(current_state == ControllerState::k_state_InitReadingState) {
    if(worker_reports.at(k_worker_bgeigie_connector).is_fresh()) {
      schedule_event(e_c_reading_initialized);
    }
  }
  return current_state;
}

void Controller::set_state(State* state) {
  Context::set_state(state);
  _state_changed = true;
}

int8_t Controller::produce_data() {
  if(_state_changed) {
    _state_changed = false;
    return WorkerStatus::e_worker_data_read;
  }
  return WorkerStatus::e_worker_idle;
}

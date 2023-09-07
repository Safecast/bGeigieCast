#include "sm_c_concrete_states.h"
#include "controller.h"
#include "identifiers.h"
#include "bgeigie_connector.h"

#define BUTTON_LONG_PRESSED_MILLIS_THRESHOLD 4000

Controller::Controller(LocalStorage& config) :
    Context(),
    Aggregator(),
    Handler(),
    Worker<SystemStateId>(k_state_InitializeState),
    _config(config),
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
  //
  schedule_event(Event_enum::e_c_controller_initialized);
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

int8_t Controller::handle_produced_work(const WorkerMap& workers) {
  const auto& button = workers.worker<Button>(k_worker_mode_button);
  if(button->is_fresh()) {
    const auto& data = button->get_data();
    switch(button->get_pin()) {
      case MODE_BUTTON_PIN:
        if(data.state == ButtonTrigger::UP && data.pressDuration > BUTTON_LONG_PRESSED_MILLIS_THRESHOLD) {
          DEBUG_PRINTLN("Button long pressed");
          schedule_event(Event_enum::e_c_button_long_pressed);
        } else if(data.state == ButtonTrigger::UP && data.pressDuration < BUTTON_LONG_PRESSED_MILLIS_THRESHOLD) {
          DEBUG_PRINTLN("Button pressed");
          schedule_event(Event_enum::e_c_button_pressed);
        }
        break;
    }
  }
  if(data == k_state_InitReadingState) {
    if(workers.worker<BGeigieConnector>(k_worker_bgeigie_connector)->is_fresh()) {
      schedule_event(e_c_reading_initialized);
    }
  }
  return e_handler_data_handled;
}

void Controller::set_state(BaseState* state) {
  Context::set_state(state);
  _state_changed = true;
}

int8_t Controller::produce_data() {
  if(_state_changed) {
    _state_changed = false;
    data = static_cast<SystemStateId>(get_current_state()->get_state_id());
    return e_worker_data_read;
  }
  return e_worker_idle;
}

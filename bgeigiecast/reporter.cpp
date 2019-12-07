#include "reporter.h"
#include "sm_r_concrete_states.h"

// Every 5 seconds
#define BGEIGIE_MEASUREMENTS_SECONDS 5
#define BGEIGIE_READING_SLACK 500
#define READING_DELAY (BGEIGIE_MEASUREMENTS_SECONDS * 1000) - BGEIGIE_READING_SLACK

Reporter::Reporter(EspConfig& config,
                   Stream& bgeigie_connection,
                   IApiConnector& api_connector,
                   BluetoohConnector& bluetooth_connector,
                   ReporterObserver* observer) :
    _bgeigie_connector(bgeigie_connection),
    _config(config),
    _api_connector(api_connector),
    _bluetooth(bluetooth_connector),
    _observer(observer),
    _last_reading(),
    _last_reading_moment(0),
    _report_bt(false),
    _report_api(false),
    _idle(false){
  _api_connector.set_observer(this);
}

void Reporter::setup_state_machine() {
  set_state(new ReporterIdleState(*this));
}

void Reporter::set_report_output(bool bt, bool api) {
  _report_bt = bt;
  _report_api = api;
  if(_report_api) {
    _api_connector.reset();
  }
}

uint32_t Reporter::time_till_next_reading(uint32_t current) const {
  return _last_reading_moment != 0 && current - _last_reading_moment < READING_DELAY ? READING_DELAY - (current - _last_reading_moment) : 0;
}

void Reporter::get_new_reading() {
  if(_bgeigie_connector.get_reading(_last_reading)) {
    _last_reading_moment = millis();
    _last_reading.get_status() & k_reading_valid ? schedule_event(e_r_reading_received) : schedule_event(e_r_reading_invalid);
    if(_last_reading.get_device_id() > 0) {
      _config.set_device_id(_last_reading.get_device_id(), false);
    }
    _config.set_last_latitude(_last_reading.get_latitude(), false);
    _config.set_last_longitude(_last_reading.get_longitude(), false);
  }
}

bool Reporter::is_idle() const {
  return _idle;
}

void Reporter::init_bluetooth_connector() {
  if(_last_reading.get_device_id()) {
    _bluetooth.init(_last_reading.get_device_id());
    schedule_event(e_r_bluetooth_initialized);
  }
}

void Reporter::run_bluetooth_connector() {
  _bluetooth.send_reading(_last_reading);
  schedule_event(e_r_reading_reported_bt);
}

void Reporter::init_api_connector() {
  _api_connector.init_reading_report(_last_reading);
  schedule_event(e_r_api_connector_initialized);
}

void Reporter::run_api_connector() {
  _api_connector.run();
}

void Reporter::set_observer(ReporterObserver* observer) {
  _observer = observer;
}

void Reporter::api_reported(IApiConnector::ReportApiStatus status) {
  switch(status) {
    case IApiConnector::k_report_success:
      schedule_event(e_r_reading_reported_api_success);
      break;
    case IApiConnector::k_report_skipped:
      schedule_event(e_r_reading_reported_api_no_change);
      break;
    case IApiConnector::k_report_failed:
      schedule_event(e_r_reading_reported_api_failed);
      break;
  }
}

void Reporter::report_complete(ReporterStatus status) {
  if(_observer) {
    _observer->reading_reported(status);
  }
  schedule_event(e_r_reading_reported);
}

const Reading& Reporter::get_last_reading() const {
  return _last_reading;
}

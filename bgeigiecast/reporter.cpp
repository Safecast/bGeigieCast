#include "reporter.h"
#include "sm_r_idle.h"

// Every 5 seconds
#define BGEIGIE_READING_SLACK 500
#define READING_DELAY (5 * 1000) - BGEIGIE_READING_SLACK

Reporter::Reporter(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector, ReporterObserver* observer) :
    _bgeigie_connector(bgeigie_connection),
    _config(config),
    _api_connector(api_connector),
    _bluetooth(bluetooth_connector),
    _observer(observer),
    _last_reading(nullptr),
    _report_bt(false),
    _report_api(false){
}

void Reporter::setup_state_machine() {
  set_state(new ReporterIdleState(*this));
}

void Reporter::set_report_output(bool bt, bool api) {
  _report_bt = bt;
  _report_api = api;
}

uint32_t Reporter::time_till_next_reading(uint32_t current) const {
  return current - _last_reading_moment > READING_DELAY ? READING_DELAY - (current - _last_reading_moment) : 0;
}

void Reporter::get_new_reading() {
  Reading* output;
  if(_bgeigie_connector.get_reading(&output) && output) {
    delete _last_reading;
    _last_reading = output;
    _last_reading_moment = millis();
    schedule_event(e_r_reading_received);
  }
}

bool Reporter::is_report_bt() const {
  return _report_bt;
}

bool Reporter::is_report_api() const {
  return _report_api;
}
bool Reporter::is_idle() const {
  return dynamic_cast<ReporterIdleState*>(get_current_state()) != nullptr;
}


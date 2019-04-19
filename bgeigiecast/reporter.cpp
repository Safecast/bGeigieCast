#include "reporter.h"

Reporter::Reporter(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector) :
    _geigie_connector(bgeigie_connection),
    _config(config),
    _api_connector(api_connector),
    _bluetooth(bluetooth_connector),
    _last_reading(),
    _report_bt(false),
    _report_api(false){

}

void Reporter::setup_state_machine() {
//  set_state();
}

void Reporter::set_report_output(bool bt, bool api) {
  _report_bt = bt;
  _report_api = api;
}

bool Reporter::is_report_bt() const {
  return _report_bt;
}
bool Reporter::is_report_api() const {
  return _report_api;
}


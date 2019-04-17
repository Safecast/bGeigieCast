#include "reporter.h"

Reporter::Reporter(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector) :
    _geigie_connector(bgeigie_connection),
    _config(config),
    _api_connector(api_connector),
    _bluetooth(bluetooth_connector) {

}

void Reporter::setup_state_machine() {
//  set_state();
}


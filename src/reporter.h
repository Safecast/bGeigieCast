#ifndef BGEIGIECAST_REPORTER_H
#define BGEIGIECAST_REPORTER_H

#include <Stream.h>

#include "i_bluetooth_connector.h"
#include "i_api_connector.h"
#include "bgeigie_connector.h"
#include "sm_context.h"

/**
 * The reporter will receive instructions to get and report readings from the bgeigie to the api / bluetooth
 */
class Reporter : public Context {
 public:

  typedef enum {
    k_reporter_failed,
    k_reporter_success,
  } ReporterStatus;

  Reporter(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector);
  virtual ~Reporter() = default;

  /**
   * Set initial state for the state machine,
   */
  void setup_state_machine();

  void set_report_output(bool bt, bool api);
  bool is_report_bt() const;
  bool is_report_api() const;

 private:
  BGeigieConnector _geigie_connector;
  IEspConfig& _config;
  IApiConnector& _api_connector;
  IBluetoohConnector& _bluetooth;

  Reading _last_reading;

  bool _report_bt;
  bool _report_api;
};

#endif //BGEIGIECAST_REPORTER_H

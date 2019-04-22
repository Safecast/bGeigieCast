#ifndef BGEIGIECAST_REPORTER_H
#define BGEIGIECAST_REPORTER_H

#include <Stream.h>

#include "i_bluetooth_connector.h"
#include "i_api_connector.h"
#include "bgeigie_connector.h"
#include "sm_context.h"

class ReporterObserver;

/**
 * The reporter will receive instructions to get and report readings from the bgeigie to the api / bluetooth
 */
class Reporter : public Context {
 public:

  typedef enum {
    k_reporter_failed,
    k_reporter_success,
  } ReporterStatus;

  Reporter(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector, ReporterObserver* observer);
  virtual ~Reporter() = default;

  /**
   * Set initial state for the state machine,
   */
  void setup_state_machine();

  /**
   * Set to which outputs the reporter should report to
   * @param bt : report over bluetooth (boolean)
   * @param api : report to api (boolean)
   */
  void set_report_output(bool bt, bool api);
  bool is_report_bt() const;
  bool is_report_api() const;

  uint32_t time_till_next_reading(uint32_t current) const;

  bool is_idle() const;

  void get_new_reading();

 private:
  BGeigieConnector _bgeigie_connector;
  IEspConfig& _config;
  IApiConnector& _api_connector;
  IBluetoohConnector& _bluetooth;

  ReporterObserver* _observer;

  Reading* _last_reading;
  uint32_t _last_reading_moment;

  bool _report_bt;
  bool _report_api;

  // Friend list
  friend class ReporterDoneState;
};

/**
 * Observing the reporter, gets callback one report is done
 */
class ReporterObserver {
  virtual void reading_reported(Reporter::ReporterStatus status) = 0;
};

#endif //BGEIGIECAST_REPORTER_H

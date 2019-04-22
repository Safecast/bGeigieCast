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
class Reporter : public Context, private ApiConnectionObserver {
 public:

  /**
   *
   */
  typedef enum {
    k_reporter_failed,
    k_reporter_success,
  } ReporterStatus;

  /**
   * Create a new reporter
   * @param config : config connection to be used for the reporter and outgoing connections
   * @param bgeigie_connection : Stream connected to the bGeigieNano (Serial)
   * @param api_connector : Wifi connector to the API
   * @param bluetooth_connector : Bluetooth connector
   * @param observer : Some instance to report to, default null
   */
  Reporter(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector, ReporterObserver* observer = nullptr);
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

  void set_observer(ReporterObserver* _observer);

 private:
  void api_reported(IApiConnector::ReportApiStatus status) override;

  /**
   * Get new reading from the bgeigie connector
   */
  void get_new_reading();

  /**
   * Initialize the bluetooth connection
   */
  void init_bluetooth_connector();

  /**
   * publish the reading over bluetooth
   */
  void run_bluetooth_connector();

  /**
   * Initialize the API connector state machine
   */
  void init_api_connector();

  /**
   * Run the api connector state machine
   */
  void run_api_connector();

  void report_complete(ReporterStatus status);


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
  friend class GetReadingState;
  friend class ReporterDoneState;
  friend class InitBluetoothState;
  friend class PublishBluetoothState;
  friend class InitApiState;
  friend class ReportApiState;
  friend class ReporterDoneState;
};

/**
 * Observing the reporter, gets callback one report is done
 */
class ReporterObserver {
 public:
  virtual void reading_reported(Reporter::ReporterStatus status) = 0;
};

#endif //BGEIGIECAST_REPORTER_H

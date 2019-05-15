#ifndef BGEIGIECAST_CONTROLLER_HPP
#define BGEIGIECAST_CONTROLLER_HPP

#include "button.h"
#include "button_observer.h"
#include "sm_context.h"
#include "conf_server.h"
#include "bgeigie_connector.h"
#include "i_api_connector.h"
#include "i_bluetooth_connector.h"
#include "mode_led.h"
#include "reporter.h"

/**
 * Main controller for the system, implements state machine to run
 */
class Controller : public Context, private ButtonObserver, private ReporterObserver {
 public:
  typedef void (*sleep_fn_t)(uint32_t millis_to_sleep);

  Controller(IEspConfig& config, Stream& bgeigie_connection, IApiConnector& api_connector, IBluetoohConnector& bluetooth_connector, sleep_fn_t sleep_fn = nullptr);
  virtual ~Controller() = default;

  /**
   * Set initial state for the state machine,
   */
  void setup_state_machine();

  /**
   * Initialize the controller and all of its components
   */
  void initialize();

  /**
   * Override the context run to also run the reporter state machine
   */
  void run() override;

  /**
   *
   */
  void set_reporter_outputs(bool bt, bool api);

  /**
   * Go to sleep till next reading is expected.
   */
  void sleep();

  /**
   * Reset and restart the system
   */
  void reset_system();

  /**
   * Callback for the button
   */
  void on_button_pressed(Button* button, uint32_t millis) override;

  /**
   * Save a state to the memory
   * @param state
   */
  void save_state(SavableState state);

  /**
   * get the saved state from the memory
   */
  SavableState get_saved_state();


 private:
  void reading_reported(Reporter::ReporterStatus status) override;

 private:
  IEspConfig& _config;
  Reporter _reporter;
  ConfigWebServer _ap_server;
  Button _mode_button;
  ModeLED _mode_led;

  sleep_fn_t _sleep_fn;


  friend class InitializeState;
  friend class InitReadingState;
  friend class PostInitializeState;
  friend class SetupServerState;
  friend class ServerActiveState;
  friend class MobileModeState;
  friend class ConnectedState;
  friend class DisconnectedState;
  friend class ConnectionErrorState;
};

#endif //BGEIGIECAST_CONTROLLER_HPP

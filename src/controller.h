#ifndef BGEIGIE_POINTCAST_CONTROLLER_HPP
#define BGEIGIE_POINTCAST_CONTROLLER_HPP

#include <button.h>
#include <button_observer.h>

#include "state_machine/context.h"
#include "web_server.h"
#include "api_connector.h"
#include "bgeigie_connector.h"
#include "bluetooth_connector.h"

class Controller : public Context, public ButtonObserver {
 public:
  Controller();
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
   * Tries to read new serial input from the bGeigie, if there is, it will report to bluetooth / api
   * @param report_bluetooth: If true, it will command the bluetooth component to process the report
   * @param report_api: If true, it will command the api component to process the report
   */
  void get_bgeigie_readings(bool report_bluetooth, bool report_api);

  /**
   * Callback for the button
   */
  void on_button_pressed(Button* button, uint32_t millis) override;
  EspConfig& get_config();
  ConfigWebServer& get_ap_server();
  ApiConnector& get_api_connector();
  Button& get_mode_button();

 private:
  EspConfig _config;
  ConfigWebServer _ap_server;
  ApiConnector _api_connector;
  Button _mode_button;
  BluetoohConnector _bluetooth;
  BGeigieConnector _bgeigie_connector;

};

#endif //BGEIGIE_POINTCAST_CONTROLLER_HPP

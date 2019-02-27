#ifndef BGEIGIE_POINTCAST_CONTROLLER_HPP
#define BGEIGIE_POINTCAST_CONTROLLER_HPP

#include <button.h>
#include <button_observer.h>

#include "state_machine/context.h"
#include "web_server.h"
#include "api_connector.h"

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

};

#endif //BGEIGIE_POINTCAST_CONTROLLER_HPP

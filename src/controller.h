#ifndef BGEIGIE_POINTCAST_CONTROLLER_HPP
#define BGEIGIE_POINTCAST_CONTROLLER_HPP

#include <button.h>
#include <button_observer.h>

#include "state_machine/context.h"
#include "web_server.h"

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
   * Initialize the access point server
   */
  void initialize_ap_server();

  /**
   * Callback for the button
   */

  EspConfig& get_config();
 private:
  void on_button_pressed(Button* button, uint32_t millis) override;
 public:
  WebServer& get_ap_server();
  const Button& get_mode_button() const;

 private:
  EspConfig _config;
  WebServer _ap_server;
  Button _mode_button;

};

#endif //BGEIGIE_POINTCAST_CONTROLLER_HPP

#ifndef BGEIGIE_POINTCAST_CONTROLLER_HPP
#define BGEIGIE_POINTCAST_CONTROLLER_HPP

#include <button.h>

#include "state_machine/context.h"
#include "web_server.h"

class Controller : public Context {
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
   * Button pressed callback
   */
  void button_pressed_cb();

  EspConfig& get_config();
  WebServer& get_ap_server();

 private:
  EspConfig _config;
  WebServer _ap_server;

};

#endif //BGEIGIE_POINTCAST_CONTROLLER_HPP

#ifndef BGEIGIECAST_CONTROLLER_HPP
#define BGEIGIECAST_CONTROLLER_HPP

#include <Handler.hpp>
#include <Aggregator.hpp>

#include "button.h"
#include "sm_context.h"
#include "local_storage.h"

/**
 * Main controller for the system, implements state machine to run
 */
class Controller : private ButtonObserver, public Context, public Aggregator, private Handler {
 public:

  typedef enum {
    k_savable_MobileMode,
    k_savable_FixedMode
  } SavableState;

  Controller(LocalStorage& config);
  virtual ~Controller() = default;

  /**
   * Set initial state for the state machine,
   */
  void setup_state_machine();

  /**
   * Override the context run to also run the reporter state machine
   */
  void run() override;

  /**
   * Callback for the button
   */
  void on_button_pressed(Button* button, uint32_t millis) override;

 protected:
  int8_t handle_produced_work(const worker_status_t& worker_reports) override;

 private:

  /**
   * Reset and restart the system
   */
  void reset_system();

  /**
   * Save a state to the memory
   * @param state
   */
  void save_state(SavableState state);

  /**
   * get the saved state from the memory
   */
  SavableState get_saved_state();

  /**
   * Initialize the controller and all of its components
   */
  void initialize();

  LocalStorage& _config;
  Button _mode_button;

  friend class InitializeState;
  friend class PostInitializeState;
  friend class ConfigurationModeState;
  friend class MobileModeState;
  friend class FixedModeState;
  friend class ResetState;
};

#endif //BGEIGIECAST_CONTROLLER_HPP

#ifndef BGEIGIECAST_CONTROLLER_HPP
#define BGEIGIECAST_CONTROLLER_HPP

#include "Handler.hpp"
#include "Aggregator.hpp"

#include "button.h"
#include "sm_context.h"
#include "local_storage.h"

enum SystemStateId {
  k_state_InitializeState,
  k_state_InitReadingState,
  k_state_PostInitializeState,
  k_state_ConfigurationModeState,
  k_state_MobileModeState,
  k_state_FixedModeState,
  k_state_ResetState,
};

/**
 * Main controller for the system, implements state machine to run
 */
class Controller : public Context, public Aggregator, public Handler, public Worker<SystemStateId> {
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
   * override set state from context, to flag worker that change has been made
   * @param state
   */
  void set_state(BaseState* state) override;

 private:
  void initialize() override;
  int8_t handle_produced_work(const worker_map_t& workers) override;

 private:
  int8_t produce_data() override;

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

  LocalStorage& _config;
  bool _state_changed;

  friend class InitializeState;
  friend class PostInitializeState;
  friend class ConfigurationModeState;
  friend class MobileModeState;
  friend class FixedModeState;
  friend class ResetState;
};

#endif //BGEIGIECAST_CONTROLLER_HPP

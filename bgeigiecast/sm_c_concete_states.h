#ifndef BGEIGIECAST_SM_C_CONCETE_STATES_H
#define BGEIGIECAST_SM_C_CONCETE_STATES_H

#include "sm_c_state.h"

class InitializeState : public ControllerState {
 public:
  explicit InitializeState(Controller& context);
  virtual ~InitializeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class InitReadingState : public ControllerState {
 public:
  explicit InitReadingState(Controller& context);
  virtual ~InitReadingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class PostInitializeState : public ControllerState {
 public:
  explicit PostInitializeState(Controller& context);
  virtual ~PostInitializeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:

  uint32_t timer;
};

class ConfigModeState : public ControllerState {
 public:
  explicit ConfigModeState(Controller& context);
  virtual ~ConfigModeState() = default;

  void handle_event(Event_enum event_id) override;
};

class SetupServerState : public ConfigModeState {
 public:
  explicit SetupServerState(Controller& context);
  virtual ~SetupServerState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ServerActiveState : public ConfigModeState {
 public:
  explicit ServerActiveState(Controller& context);
  virtual ~ServerActiveState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ActiveState : public ControllerState {
 public:
  explicit ActiveState(Controller& context);
  virtual ~ActiveState() = default;

  void do_activity() override;

  void handle_event(Event_enum event_id) override;
};

class InitActiveState : public ActiveState {
 public:
  explicit InitActiveState(Controller& context);
  virtual ~InitActiveState() = default;

  void do_activity() override;
  void entry_action() override;
  void exit_action() override;

  void handle_event(Event_enum event_id) override;

};

class MobileModeState : public ActiveState {
 public:
  explicit MobileModeState(Controller& context);
  virtual ~MobileModeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

class FixedModeState : public ActiveState {
 public:
  explicit FixedModeState(Controller& context);
  virtual ~FixedModeState() = default;

  void do_activity() override;

  void handle_event(Event_enum event_id) override;

};

class DisconnectedState : public FixedModeState {
 public:
  explicit DisconnectedState(Controller& context);
  virtual ~DisconnectedState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:
  uint32_t state_entry_moment;
};

class ConnectedState : public FixedModeState {
 public:
  explicit ConnectedState(Controller& context);
  virtual ~ConnectedState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

class ConnectionErrorState : public FixedModeState {
 public:
  explicit ConnectionErrorState(Controller& context);
  virtual ~ConnectionErrorState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:
  uint32_t timer;
};

class ResetState : public ControllerState {
 public:
  explicit ResetState(Controller& context);
  virtual ~ResetState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

#endif //BGEIGIECAST_SM_C_CONCETE_STATES_H

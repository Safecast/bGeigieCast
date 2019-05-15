#ifndef BGEIGIECAST_SM_R_CONCRETE_STATES_H
#define BGEIGIECAST_SM_R_CONCRETE_STATES_H

#include "sm_r_state.h"

class ReporterIdleState : public ReporterState {
 public:
  explicit ReporterIdleState(Reporter& context);
  virtual ~ReporterIdleState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class GetReadingState : public ReporterState {
 public:
  explicit GetReadingState(Reporter& context);
  virtual ~GetReadingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ReportReadingState : public ReporterState {
 public:
  explicit ReportReadingState(Reporter& context);
  virtual ~ReportReadingState() = default;

  void handle_event(Event_enum event_id) override;
};

class InitBluetoothState : public ReportReadingState {
 public:
  explicit InitBluetoothState(Reporter& context);
  virtual ~InitBluetoothState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class PublishBluetoothState : public ReportReadingState {
 public:
  explicit PublishBluetoothState(Reporter& context);
  virtual ~PublishBluetoothState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class InitApiState : public ReportReadingState {
 public:
  explicit InitApiState(Reporter& context);
  virtual ~InitApiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ReportApiState : public ReportReadingState {
 public:
  explicit ReportApiState(Reporter& context);
  virtual ~ReportApiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ReporterDoneState : public ReportReadingState {
 public:
  explicit ReporterDoneState(Reporter& context, Reporter::ReporterStatus status);
  virtual ~ReporterDoneState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:
  Reporter::ReporterStatus status;

};

#endif //BGEIGIECAST_SM_R_CONCRETE_STATES_H

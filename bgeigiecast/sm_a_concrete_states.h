#ifndef BGEIGIECAST_SM_A_CONCRETE_STATES_H
#define BGEIGIECAST_SM_A_CONCRETE_STATES_H


#include "sm_a_state.h"

class ApiProcessReadingState : public ApiReporterState {
 public:
  explicit ApiProcessReadingState(IApiConnector& context, Reading* reading);
  virtual ~ApiProcessReadingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ConnectWiFiState : public ApiReporterState {
 public:
  explicit ConnectWiFiState(IApiConnector& context, Reading* reading);
  virtual ~ConnectWiFiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:
  uint32_t _start_time;
  uint32_t _last_connect_try;
};

//class ReconnectWiFiState : public ApiReporterState {
// public:
//  explicit ReconnectWiFiState(IApiConnector& context, Reading* reading);
//  virtual ~ConnectWiFiState() = default;
//
//  void entry_action() override;
//  void do_activity() override;
//  void exit_action() override;
//  void handle_event(Event_enum event_id) override;
// private:
//  uint32_t _start_time;
//  uint32_t _last_connect_try;
//};

class PublishApiState : public ApiReporterState {
 public:
  explicit PublishApiState(IApiConnector& context, Reading* reading);
  virtual ~PublishApiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class ApiReportFailedState : public ApiReporterState {
 public:
  explicit ApiReportFailedState(IApiConnector& context, Reading* reading);
  virtual ~ApiReportFailedState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

class PublishSavedApiState : public PublishApiState {
 public:
  explicit PublishSavedApiState(IApiConnector& context, Reading* reading);
  virtual ~PublishSavedApiState() = default;

  void handle_event(Event_enum event_id) override;
};

class ApiReportSavedFailedState : public ApiReportFailedState {
 public:
  explicit ApiReportSavedFailedState(IApiConnector& context, Reading* reading);
  virtual ~ApiReportSavedFailedState() = default;

  void handle_event(Event_enum event_id) override;
 private:

};

class ApiReportDoneState : public ApiReporterState {
 public:
  explicit ApiReportDoneState(IApiConnector& context, IApiConnector::ReportApiStatus status);
  virtual ~ApiReportDoneState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:
  IApiConnector::ReportApiStatus status;
};

#endif //BGEIGIECAST_SM_A_CONCRETE_STATES_H

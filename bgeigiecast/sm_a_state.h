#ifndef BGEIGIECAST_SM_R_STATE_H
#define BGEIGIECAST_SM_R_STATE_H

#include "i_api_connector.h"
#include "sm_state.h"

/**
 * State with api connector context, so the states can control the api connection
 */
class ApiReporterState : public State {
 public:
  explicit ApiReporterState(IApiConnector& context): api_connector(context){};
  virtual ~ApiReporterState() = default;
 protected:
  IApiConnector& api_connector;
};

class ApiReporterReadingState : public ApiReporterState {
 public:
  explicit ApiReporterReadingState(IApiConnector& context, Reading& reading): ApiReporterState(context), reading(reading){};
  virtual ~ApiReporterReadingState() = default;
 protected:
  Reading& reading;
};

#endif //BGEIGIECAST_SM_R_STATE_H

#ifndef BGEIGIECAST_SM_R_STATE_H
#define BGEIGIECAST_SM_R_STATE_H

#include "i_api_connector.h"
#include "sm_state.h"

/**
 * State with api connector context, so the states can control the api connection
 */
class ApiReporterState: public State {
 public:
  explicit ApiReporterState(IApiConnector& context, Reading* reading): api_connector(context), reading(reading){};
  virtual ~ApiReporterState() = default;
 protected:
  IApiConnector& api_connector;
  Reading* reading;
};

#endif //BGEIGIECAST_SM_R_STATE_H

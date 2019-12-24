#ifndef BGEIGIECAST_SM_R_STATE_H
#define BGEIGIECAST_SM_R_STATE_H

#include "reporter.h"
#include "sm_state.h"

/**
 * State with reporter context, so the states can control the reporter
 */
class ReporterState : public State {
 public:
  explicit ReporterState(Reporter& context) : reporter(context) {};
  virtual ~ReporterState() = default;
 protected:
  Reporter& reporter;
};

#endif //BGEIGIECAST_SM_R_STATE_H

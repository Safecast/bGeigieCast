#ifndef BGEIGIECAST_SM_R_RR_PUBLISH_API_H
#define BGEIGIECAST_SM_R_RR_PUBLISH_API_H


#include "sm_a_state.h"

class PublishApiState : public ApiReporterState {
 public:
  explicit PublishApiState(IApiConnector& context, Reading* reading);
  virtual ~PublishApiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
};

#endif //BGEIGIECAST_SM_R_RR_PUBLISH_API_H

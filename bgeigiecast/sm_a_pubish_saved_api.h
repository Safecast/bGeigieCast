#ifndef BGEIGIECAST_SM_A_PUBISH_SAVED_API_H
#define BGEIGIECAST_SM_A_PUBISH_SAVED_API_H

#include "sm_a_state.h"
#include "sm_a_publish_api.h"

class PublishSavedApiState : public PublishApiState {
 public:
  explicit PublishSavedApiState(IApiConnector& context, Reading* reading);
  virtual ~PublishSavedApiState() = default;

  void handle_event(Event_enum event_id) override;
 private:
};

#endif //BGEIGIECAST_SM_A_PUBISH_SAVED_API_H

#ifndef BGEIGIECAST_CONNECTINGSTATE_H
#define BGEIGIECAST_CONNECTINGSTATE_H

#include "sm_c_active_fixed.h"


class DisconnectedState: public FixedModeState {
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

#endif //BGEIGIECAST_CONNECTINGSTATE_H

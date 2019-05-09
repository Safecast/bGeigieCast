#ifndef BGEIGIECAST_CONNECTIONERRORSTATE_HPP
#define BGEIGIECAST_CONNECTIONERRORSTATE_HPP

#include "sm_c_active_fixed.h"

class ConnectionErrorState: public FixedModeState {
 public:
  explicit ConnectionErrorState(Controller& context);
  virtual ~ConnectionErrorState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:
  uint32_t timer;
  bool blink_state;
};

#endif //BGEIGIECAST_CONNECTIONERRORSTATE_HPP
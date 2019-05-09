#ifndef BGEIGIECAST_RESETSTATE_HPP
#define BGEIGIECAST_RESETSTATE_HPP

#include "sm_c_state.h"

class ResetState : public ControllerState {
 public:
  explicit ResetState(Controller& context);
  virtual ~ResetState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_RESETSTATE_HPP
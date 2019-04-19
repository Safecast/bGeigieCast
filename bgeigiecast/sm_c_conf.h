#ifndef BGEIGIECAST_CONFSTATE_HPP
#define BGEIGIECAST_CONFSTATE_HPP

#include "sm_c_state.h"

class ConfigModeState: public ControllerState {
 public:
  explicit ConfigModeState(Controller& context);
  virtual ~ConfigModeState() = default;

  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_CONFSTATE_HPP

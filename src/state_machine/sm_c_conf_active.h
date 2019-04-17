#ifndef BGEIGIE_POINTCAST_SERVERACTIVESTATE_HPP
#define BGEIGIE_POINTCAST_SERVERACTIVESTATE_HPP

#include "sm_c_state.h"

class ServerActiveState: public State {
 public:
  ServerActiveState(Controller& context);
  virtual ~ServerActiveState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIE_POINTCAST_SERVERACTIVESTATE_HPP

#ifndef BGEIGIE_POINTCAST_SETUPSERVERSTATE_HPP
#define BGEIGIE_POINTCAST_SETUPSERVERSTATE_HPP

#include "state.h"

class SetupServerState: public State {
 public:
  SetupServerState(Controller& context);
  virtual ~SetupServerState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIE_POINTCAST_SETUPSERVERSTATE_HPP

#ifndef BGEIGIECAST_SETUPSERVERSTATE_HPP
#define BGEIGIECAST_SETUPSERVERSTATE_HPP

#include "sm_c_conf.h"

class SetupServerState: public ConfigModeState {
 public:
  explicit SetupServerState(Controller& context);
  virtual ~SetupServerState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SETUPSERVERSTATE_HPP

#ifndef BGEIGIECAST_SERVERACTIVESTATE_HPP
#define BGEIGIECAST_SERVERACTIVESTATE_HPP

#include "sm_c_conf.h"

class ServerActiveState: public ConfigModeState {
 public:
  explicit ServerActiveState(Controller& context);
  virtual ~ServerActiveState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SERVERACTIVESTATE_HPP

#ifndef BGEIGIECAST_INITACTIVESTATE_H
#define BGEIGIECAST_INITACTIVESTATE_H

#include "sm_c_active.h"

class InitActiveState: public ActiveState {
 public:
  explicit InitActiveState(Controller& context);
  virtual ~InitActiveState() = default;

  void do_activity() override;
  void entry_action() override;
  void exit_action() override;

  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIECAST_INITACTIVESTATE_H

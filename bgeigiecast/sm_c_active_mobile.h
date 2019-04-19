#ifndef BGEIGIECAST_MOBILEMODESTATE_H
#define BGEIGIECAST_MOBILEMODESTATE_H

#include "sm_c_active.h"

class MobileModeState: public ActiveState {
 public:
  explicit MobileModeState(Controller& context);
  virtual ~MobileModeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIECAST_MOBILEMODESTATE_H

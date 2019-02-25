#ifndef BGEIGIE_POINTCAST_MOBILEMODESTATE_H
#define BGEIGIE_POINTCAST_MOBILEMODESTATE_H

#include "../ActiveState.h"

class MobileModeState: public ActiveState {
 public:
  MobileModeState(Controller& context);
  virtual ~MobileModeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_MOBILEMODESTATE_H

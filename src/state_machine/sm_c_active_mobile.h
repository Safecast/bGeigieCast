#ifndef BGEIGIE_POINTCAST_MOBILEMODESTATE_H
#define BGEIGIE_POINTCAST_MOBILEMODESTATE_H

#include "../ActiveState__.h"

class MobileModeState__: public ActiveState__ {
 public:
  MobileModeState__(Controller& context);
  virtual ~MobileModeState__() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_MOBILEMODESTATE_H

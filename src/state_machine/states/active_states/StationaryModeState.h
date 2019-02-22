#ifndef BGEIGIE_POINTCAST_STATIONARYMODESTATE_H
#define BGEIGIE_POINTCAST_STATIONARYMODESTATE_H

#include "../ActiveState.h"

class StationaryModeState: public ActiveState {
 public:
  StationaryModeState(Controller& context);
  virtual ~StationaryModeState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_STATIONARYMODESTATE_H

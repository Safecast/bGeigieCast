#ifndef BGEIGIE_POINTCAST_STATIONARYMODESTATE_H
#define BGEIGIE_POINTCAST_STATIONARYMODESTATE_H

#include "../ActiveState.h"

class StationaryModeState: public ActiveState {
 public:
  StationaryModeState(Controller& context);
  virtual ~StationaryModeState() = default;

  void do_activity() override;

  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_STATIONARYMODESTATE_H

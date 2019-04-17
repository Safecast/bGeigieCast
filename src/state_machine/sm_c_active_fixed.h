#ifndef BGEIGIE_POINTCAST_STATIONARYMODESTATE_H
#define BGEIGIE_POINTCAST_STATIONARYMODESTATE_H

#include "../ActiveState__.h"

class StationaryModeState__: public ActiveState__ {
 public:
  StationaryModeState__(Controller& context);
  virtual ~StationaryModeState__() = default;

  void do_activity() override;

  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_STATIONARYMODESTATE_H

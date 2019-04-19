#ifndef BGEIGIECAST_STATIONARYMODESTATE_H
#define BGEIGIECAST_STATIONARYMODESTATE_H

#include "sm_c_active.h"

class FixedModeState: public ActiveState {
 public:
  explicit FixedModeState(Controller& context);
  virtual ~FixedModeState() = default;

  void do_activity() override;

  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIECAST_STATIONARYMODESTATE_H

#ifndef BGEIGIE_POINTCAST_CONNECTINGSTATE_H
#define BGEIGIE_POINTCAST_CONNECTINGSTATE_H

// 10 seconds of wifi connect,  5 is just to low, will sometimes take a bit longer
#define MILLIS_BEFORE_CONNECTION_FAILURE 10000

#include "../StationaryModeState.h"


class ConnectingState: public StationaryModeState {
 public:
  ConnectingState(Controller& context);
  virtual ~ConnectingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:
  uint32_t timer;
};

#endif //BGEIGIE_POINTCAST_CONNECTINGSTATE_H

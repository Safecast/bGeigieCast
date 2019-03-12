#ifndef BGEIGIE_POINTCAST_RECONNECTINGSTATE_H
#define BGEIGIE_POINTCAST_RECONNECTINGSTATE_H

#include "../StationaryModeState.h"


class ReconnectingState: public StationaryModeState {
 public:
  ReconnectingState(Controller& context);
  virtual ~ReconnectingState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

 private:
  uint32_t timer;
};
#endif //BGEIGIE_POINTCAST_RECONNECTINGSTATE_H

#ifndef BGEIGIE_POINTCAST_CONNECTIONERRORSTATE_HPP
#define BGEIGIE_POINTCAST_CONNECTIONERRORSTATE_HPP

#include "../StationaryModeState.h"

class ConnectionErrorState: public StationaryModeState {
 public:
  ConnectionErrorState(Controller& context);
  virtual ~ConnectionErrorState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_CONNECTIONERRORSTATE_HPP

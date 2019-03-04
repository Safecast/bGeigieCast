#ifndef BGEIGIE_POINTCAST_TESTAPISTATE_HPP
#define BGEIGIE_POINTCAST_TESTAPISTATE_HPP

#include "../StationaryModeState.h"

class TestApiState: public StationaryModeState {
 public:
  TestApiState(Controller& context);
  virtual ~TestApiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;

};

#endif //BGEIGIE_POINTCAST_TESTAPISTATE_HPP

#include "StationaryModeState.h"
#include "MobileModeState.h"

StationaryModeState::StationaryModeState(Controller& context) : ActiveState(context) {
}

void StationaryModeState::do_activity() {
  controller.process_possible_bgeigie_readings(true, true);
}

void StationaryModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.get_api_connector().stop();
      controller.set_state(new MobileModeState(controller));
      break;
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

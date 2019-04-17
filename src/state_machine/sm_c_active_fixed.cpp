#include "StationaryModeState__.h"
#include "MobileModeState__.h"

StationaryModeState__::StationaryModeState__(Controller& context) : ActiveState__(context) {
}

void StationaryModeState__::do_activity() {
  controller.process_possible_bgeigie_readings(true, true);
}

void StationaryModeState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_pressed:
      controller.get_api_connector().stop();
      controller.set_state(new MobileModeState__(controller));
      break;
    default:
      ActiveState__::handle_event(event_id);
      break;
  }
}

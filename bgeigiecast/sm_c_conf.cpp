#include "sm_c_conf.h"

ConfigModeState::ConfigModeState(Controller& context): ControllerState(context) {
}

void ConfigModeState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

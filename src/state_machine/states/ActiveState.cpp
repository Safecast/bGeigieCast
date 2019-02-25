#include "ActiveState.h"
#include "ResetState.hpp"

ActiveState::ActiveState(Controller& context): State(context) {
}
void ActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_long_pressed:
      controller.get_api_connector().stop();
      controller.set_state(new ResetState(controller));
      break;
    default:
      State::handle_event(event_id);
      break;
  }
}

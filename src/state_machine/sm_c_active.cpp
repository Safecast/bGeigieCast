#include "ActiveState__.h"
#include "ResetState__.hpp"

ActiveState__::ActiveState__(Controller& context): State(context) {
}
void ActiveState__::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_button_long_pressed:
      controller.get_api_connector().stop();
      controller.set_state(new ResetState__(controller));
      break;
    default:
      State::handle_event(event_id);
      break;
  }
}

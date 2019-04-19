#include "sm_c_active_f_conn.h"
#include "sm_c_active_f_disconn.h"

ConnectedState::ConnectedState(Controller& context): FixedModeState(context) {
}

void ConnectedState::entry_action() {
  DEBUG_PRINTLN("Entered state Connected");
  controller.get_state_led().set_color(StateLED::StateColor::fixed_active);
}

void ConnectedState::do_activity() {
  FixedModeState::do_activity();
}

void ConnectedState::exit_action() {
}

void ConnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_api_report_failed:
      controller.set_state(new DisconnectedState(controller));
      break;
    default:
      FixedModeState::handle_event(event_id);
      break;
  }
}

#include "sm_c_active_f_disconn.h"
#include "sm_c_active_f_connerr.h"
#include "sm_c_active_f_conn.h"

DisconnectedState::DisconnectedState(Controller& context): FixedModeState(context), state_entry_moment(0) {
}

void DisconnectedState::entry_action() {
  DEBUG_PRINTLN("Entered state FixedMode, Disconnected");
  controller.save_state(k_savable_FixedMode);
  controller.get_state_led().set_color(StateLED::StateColor::fixed_connecting);
}

void DisconnectedState::do_activity() {
  FixedModeState::do_activity();
}

void DisconnectedState::exit_action() {
}

void DisconnectedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_api_report_success:
      controller.set_state(new ConnectedState(controller));
      break;
    case e_c_api_report_failed:
      controller.set_state(new ConnectionErrorState(controller));
      break;
    default:
      FixedModeState::handle_event(event_id);
      break;
  }
}

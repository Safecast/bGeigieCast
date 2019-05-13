#include "sm_c_active_f_connerr.h"
#include "sm_c_active_f_conn.h"

#define BLINK_FREQUENCY_MILLIS 4000

ConnectionErrorState::ConnectionErrorState(Controller& context) : FixedModeState(context), timer(0), blink_state(false) {
}

void ConnectionErrorState::entry_action() {
  DEBUG_PRINTLN("Entered state ConnectionError");
  controller._state_led.set_color(StateLED::StateColor::fixed_error);
  timer = millis();
}

void ConnectionErrorState::do_activity() {
  FixedModeState::do_activity();
}

void ConnectionErrorState::exit_action() {
}

void ConnectionErrorState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_report_success:
      controller.set_state(new ConnectedState(controller));
      break;
    case e_c_report_failed:
      // Failed, Nothing happening already in connection error state
      break;
    default:
      FixedModeState::handle_event(event_id);
      break;
  }
}

#include "sm_r_rr_init_api.h"
#include "sm_r_rr_report_api.h"

InitApiState::InitApiState(Reporter& context) : ReportReadingState(context) {
}

void InitApiState::entry_action() {
#if DEBUG_LOG_STATE_TRANSITIONS
  DEBUG_PRINTLN("Reporter entered state Init api");
#endif
}

void InitApiState::do_activity() {
  reporter.init_api_connector();
}

void InitApiState::exit_action() {
}

void InitApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_api_connector_initialized:
      reporter.set_state(new ReportApiState(reporter));
      break;
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

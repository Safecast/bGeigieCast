#include "sm_c_active_init.h"
#include "sm_c_active_mobile.h"
#include "sm_c_active_f_disconn.h"

InitActiveState::InitActiveState(Controller& context) : ActiveState(context) {
}

void InitActiveState::entry_action() {
  DEBUG_PRINTLN("Entered state ActiveInit");
}

void InitActiveState::do_activity() {
  DEBUG_PRINTLN("oiii");
  switch(controller.get_saved_state()) {
    case k_savable_FixedMode:
      controller.set_state(new DisconnectedState(controller));
      break;
    case k_savable_MobileMode:
    default:
      controller.set_state(new MobileModeState(controller));
      break;
  }
}

void InitActiveState::exit_action() {

}

void InitActiveState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ActiveState::handle_event(event_id);
      break;
  }
}

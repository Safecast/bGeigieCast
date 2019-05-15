#include "sm_c_init_reading.h"
#include "sm_c_post_init.h"

#define BLINK_FREQUENCY 1
#define BLINK_DURATION_PERCENTAGE 10

InitReadingState::InitReadingState(Controller& context) : ControllerState(context) {
}

void InitReadingState::entry_action() {
  DEBUG_PRINTLN("Entered state Initialize reading");
  controller._state_led.set_color(StateLED::StateColor::init);
}

void InitReadingState::do_activity() {
  controller._state_led.blink(StateLED::StateColor::init, BLINK_FREQUENCY, BLINK_DURATION_PERCENTAGE);
  controller._reporter.run();
  if(controller._reporter.get_last_reading()) {
    controller.schedule_event(e_c_reading_initialized);
  }
}

void InitReadingState::exit_action() {

}

void InitReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_c_reading_initialized: {
      controller.set_state(new PostInitializeState(controller));
      break;
    }
    default:
      ControllerState::handle_event(event_id);
      break;
  }
}

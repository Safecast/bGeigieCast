#include "sm_r_rr_publish_api.h"

PublishApiState::PublishApiState(Reporter& context) : ReportReadingState(context) {

}
void PublishApiState::entry_action() {

}
void PublishApiState::do_activity() {

}
void PublishApiState::exit_action() {

}
void PublishApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReportReadingState::handle_event(event_id);
      break;
  }
}

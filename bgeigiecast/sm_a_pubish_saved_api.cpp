#include "sm_a_pubish_saved_api.h"
#include "sm_a_reporting_done.h"
#include "sm_a_failed.h"
#include "sm_a_s_failed.h"

PublishSavedApiState::PublishSavedApiState(IApiConnector& context, Reading* reading) : PublishApiState(context, reading) {
}

void PublishSavedApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_api_post_failed:
      api_connector.set_state(new ApiReportSavedFailedState(api_connector, reading));
      break;
    case e_a_reading_posted:
      PublishApiState::handle_event(event_id);
      delete reading;
      break;
    default:
      PublishApiState::handle_event(event_id);
      break;
  }
}

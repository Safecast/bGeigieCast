#include "sm_a_publish_api.h"
#include "sm_a_failed.h"
#include "sm_a_reporting_done.h"
#include "sm_a_pubish_saved_api.h"

PublishApiState::PublishApiState(IApiConnector& context, Reading* reading) : ApiReporterState(context, reading) {
}

void PublishApiState::entry_action() {
}

void PublishApiState::do_activity() {
}

void PublishApiState::exit_action() {
}

void PublishApiState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_api_post_failed:
      api_connector.set_state(new ApiReportFailedState(api_connector, reading));
      break;
    case e_a_reading_posted:
      if(api_connector._saved_readings.get_count() > 0) {
        Reading* next_saved = api_connector._saved_readings.get();
        api_connector.set_state(new PublishSavedApiState(api_connector, next_saved));
      } else {
        api_connector.set_state(new ApiReportDoneState(api_connector, IApiConnector::k_report_success));
      }
      break;
    default:
      ApiReporterState::handle_event(event_id);
      break;
  }
}


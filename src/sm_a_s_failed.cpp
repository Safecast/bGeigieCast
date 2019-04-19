#include "sm_a_s_failed.h"
#include "sm_a_reporting_done.h"

ApiReportSavedFailedState::ApiReportSavedFailedState(IApiConnector& context, Reading* reading) : ApiReportFailedState(context, reading) {

}

void ApiReportSavedFailedState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_a_reading_saved:
      ApiReportFailedState::handle_event(event_id);
      delete reading;
      break;
    default:
      ApiReportFailedState::handle_event(event_id);
      break;
  }
}

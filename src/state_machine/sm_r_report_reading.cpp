#include "sm_r_report_reading.h"

ReportReadingState::ReportReadingState(Reporter& context) : ReporterState(context) {
}

void ReportReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

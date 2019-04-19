#include "sm_r_report_reading.h"
#include "sm_r_idle.h"

ReportReadingState::ReportReadingState(Reporter& context) : ReporterState(context) {
}

void ReportReadingState::handle_event(Event_enum event_id) {
  switch(event_id) {
    case e_r_reading_reported:
      reporter.set_state(new ReporterIdleState(reporter));
      break;
    default:
      ReporterState::handle_event(event_id);
      break;
  }
}

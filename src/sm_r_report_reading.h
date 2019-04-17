#ifndef BGEIGIECAST_SM_R_REPORT_READING_H
#define BGEIGIECAST_SM_R_REPORT_READING_H

#include "sm_r_state.h"

class ReportReadingState : public ReporterState {
 public:
  explicit ReportReadingState(Reporter& context);
  virtual ~ReportReadingState() = default;

  void handle_event(Event_enum event_id) override;
 private:

};


#endif //BGEIGIECAST_SM_R_REPORT_READING_H

#ifndef BGEIGIECAST_SM_R_RR_DONE_H
#define BGEIGIECAST_SM_R_RR_DONE_H

#include "sm_r_report_reading.h"

class ReporterDoneState : public ReportReadingState {
 public:
  explicit ReporterDoneState(Reporter& context, Reporter::ReporterStatus status);
  virtual ~ReporterDoneState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:
  Reporter::ReporterStatus status;

};

#endif //BGEIGIECAST_SM_R_RR_DONE_H

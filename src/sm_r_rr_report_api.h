#ifndef BGEIGIECAST_SM_R_RR_REPORT_API_H
#define BGEIGIECAST_SM_R_RR_REPORT_API_H

#include "sm_r_report_reading.h"

class ReportApiState : public ReportReadingState {
 public:
  explicit ReportApiState(Reporter& context);
  virtual ~ReportApiState() = default;

  void entry_action() override;
  void do_activity() override;
  void exit_action() override;
  void handle_event(Event_enum event_id) override;
 private:

};

#endif //BGEIGIECAST_SM_R_RR_REPORT_API_H

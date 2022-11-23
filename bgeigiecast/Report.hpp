//
// Created by Jelle Bouwhuis on 12/24/19.
//

#ifndef SENSOR_REPORTER_INCLUDE_REPORT_HPP_
#define SENSOR_REPORTER_INCLUDE_REPORT_HPP_

#include "Status.hpp"

class Aggregator;

/**
 * The report object keeps track of the activity of the workers and handlers. It provides the work reports to the
 * handlers, which will then fill in the handler report. The supervisor will get the full report to handle the rest.
 */
class Report {
 public:
  Report() : worker_stats(), handler_stats() {}

  virtual ~Report() = default;

  const worker_status_t& get_worker_stats() const {
    return worker_stats;
  }

  const handler_status_t& get_handler_stats() const {
    return handler_stats;
  }

 private:
  worker_status_t worker_stats;
  handler_status_t handler_stats;
  friend Aggregator;
};

#endif //SENSOR_REPORTER_INCLUDE_REPORT_HPP_

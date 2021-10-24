//
// Created by Jelle Bouwhuis on 12/24/19.
//

#ifndef SENSOR_REPORTER_REPORTHANDLER_HPP_
#define SENSOR_REPORTER_REPORTHANDLER_HPP_

/**
 * Supervisor will oversee the full report. Mainly used for outputting all possible values (for example, put data on
 * a screen or LED).
 */
class Supervisor {
 public:
  Supervisor() = default;
  virtual ~Supervisor() = default;

  virtual bool activate() { return true; }

  /**
   * handle the full report
   * @param report
   */
  virtual void handle_report(const Report& report) = 0;

};

#endif //SENSOR_REPORTER_REPORTHANDLER_HPP_

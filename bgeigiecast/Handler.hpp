//
// Created by Jelle Bouwhuis on 12/24/19.
//

#ifndef SENSOR_REPORTER_REPORTER_HPP_
#define SENSOR_REPORTER_REPORTER_HPP_

#include "Report.hpp"
#include "Activatable.hpp"

/**
 * The handler can report the produced work to some desired output or handle it internally.
 */
class Handler : public Activatable {
 public:
  /**
   * Construct a handler
   * @param handler_id: unique id of the handler
   */
  explicit Handler(uint8_t handler_id);
  virtual ~Handler() = default;

  /**
   * Gets the handler id
   * @return handler id
   */
  virtual uint8_t get_handler_id() final;

  /**
   * Call the data handler sequence to report worker_reports
   * @param work_reports: worker reports to handle
   * @param status: reference to the status to fill of this data handler
   */
  virtual void try_handle_work(HandlerStatus& status, worker_status_t& work_reports) final;

 protected:
  /**
   * Handle the data produced by workers
   * @param worker_reports: All the data from the workers
   * @return status code (HandlerStatus::StatusCode or any custom)
   */
  virtual int8_t handle_produced_work(const worker_status_t& worker_reports) = 0;


 private:
  uint8_t handler_id;
};

#endif //SENSOR_REPORTER_REPORTER_HPP_

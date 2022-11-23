//
// Created by Jelle Bouwhuis on 12/28/19.
//

#ifndef SENSOR_HANDLER_INCLUDE_STATUS_HPP_
#define SENSOR_HANDLER_INCLUDE_STATUS_HPP_

#include <map>

/**
 * Base status for worker report and handler status
 */
struct _Status {
  typedef enum State{
    e_state_inactive = 0,
    e_state_activating_failed,
    e_state_active
  } State;

  State active_state = e_state_inactive;
  bool active() const {return active_state == e_state_active;}
};

/**
 * The produced work of a worker
 */
struct WorkerStatus : public _Status {
  /// Enum can be replaced with custom implementation, or use custom enum starting at `= 1`
  typedef enum Status {
    e_worker_idle = -1,
    e_worker_data_read,
    e_worker_error,
  } Status;

  int8_t status = Status::e_worker_idle;
  void* data = nullptr;

  bool is_fresh() const { return active_state == e_state_active && status == e_worker_data_read;}

  /**
   * Get the data as type T
   * @tparam T: type of the data
   * @return the data
   */
  template<typename T>
  const T& get() const {
    return *static_cast<T*>(data);
  }
};

typedef std::map<uint8_t, WorkerStatus> worker_status_t;

/**
 * The results of the handler handling work reports
 */
struct HandlerStatus : public _Status {
  /// Enum can be replaced with custom implementation, or use custom enum starting at `= 1`
  typedef enum Status {
    e_handler_idle = -1,
    e_handler_data_handled,
    e_handler_error,
  } Status;

  int8_t status = 0; // Custom error codes can be used
};

typedef std::map<uint8_t, HandlerStatus> handler_status_t;


#endif //SENSOR_HANDLER_INCLUDE_STATUS_HPP_

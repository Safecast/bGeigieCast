//
// Created by Jelle Bouwhuis on 12/24/19.
//

#include "Handler.hpp"

Handler::Handler(uint8_t handler_id) : Activatable(), handler_id(handler_id) {
}

void Handler::try_handle_work(HandlerStatus& status, worker_status_t& work_reports) {
  if(status.active_state == _Status::e_state_inactive) {
    // Not active
    return;
  }
  if(status.active_state == _Status::e_state_activating_failed) {
    // Still activating, will try to activate again
    if (activate(true)) {
      status.active_state = HandlerStatus::e_state_active;
    }
    else {
      return;
    }
  }
  status.status = handle_produced_work(work_reports);
}

uint8_t Handler::get_handler_id() {
  return handler_id;
}

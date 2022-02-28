//
// Created by Jelle Bouwhuis on 12/24/19.
//

#include <Aggregator.hpp>

Aggregator::Aggregator() : report() {

}

void Aggregator::register_worker(BaseWorker& worker, bool activate /* = true*/) {
  auto receiver_id = worker.get_worker_id();
  if(workers.find(receiver_id) == workers.end()) {
    // Create new worker and measurement
    workers[receiver_id] = &worker;
    report.worker_stats[receiver_id] = WorkerStatus();
    if(activate) {
      worker.set_active(true, report.worker_stats[receiver_id]);
    }
  } else {
    // Receiver with this id already exists...
    // TODO: add error logging
  }
}

void Aggregator::register_handler(Handler& handler, bool activate /* = true*/) {
  auto handler_id = handler.get_handler_id();
  if(handlers.find(handler_id) == handlers.end()) {
    // Create new handler
    handlers[handler_id] = &handler;
    report.handler_stats[handler_id] = HandlerStatus();
    if(activate) {
      handler.set_active(true, report.handler_stats[handler_id]);
    }
  } else {
    // Observer with this id already exists...
    // TODO: add error logging
  }
}

void Aggregator::register_supervisor(Supervisor& supervisor) {
  supervisors.push_back(&supervisor);
  supervisor.activate();
}

void Aggregator::run() {
  bool any_new = false;
  // get worker_reports from the data workers
  for(const auto& w : workers) {
    auto& worker = w.second;
    auto& worker_status = report.worker_stats[w.first];
    if(worker && worker->work(worker_status)) {
      any_new = true;
    }
  }
  // If no new worker_reports, skip the cycle
  if(!any_new) {
    return;
  }
  // Report the worker_reports
  for(const auto& r : handlers) {
    auto handler = r.second;
    if(handler) {
      handler->try_handle_work(report.handler_stats.at(handler->get_handler_id()), report.worker_stats);
    }
  }
  // Handle the final report
  for(const auto& report_handler : supervisors) {
    if(report_handler) {
      report_handler->handle_report(report);
    }
  }
}

void Aggregator::set_worker_active(uint8_t worker_id, bool active) {
  workers.at(worker_id)->set_active(active, report.worker_stats.at(worker_id));
}

void Aggregator::set_handler_active(uint8_t handler_id, bool active) {
  handlers.at(handler_id)->set_active(active, report.handler_stats.at(handler_id));
}

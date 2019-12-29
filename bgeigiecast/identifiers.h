#ifndef BGEIGIECAST_IDENTIFIERS_H_
#define BGEIGIECAST_IDENTIFIERS_H_

enum DataWorkers {
  k_worker_bgeigie_connector = 0,
  k_worker_configuration_server,
};

enum DataHandlers {
  k_handler_controller_handler = 0,
  k_handler_storage_handler,
  k_handler_bluetooth_reporter,
  k_handler_api_reporter,
};


#endif //BGEIGIECAST_IDENTIFIERS_H_

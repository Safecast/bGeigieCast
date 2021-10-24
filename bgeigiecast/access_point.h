#ifndef BGEIGIECAST_ACCESS_POINT_SERVER_H_
#define BGEIGIECAST_ACCESS_POINT_SERVER_H_

#include "Worker.hpp"

#include "local_storage.h"

class AccessPoint : public Worker<bool> {
 public:
  explicit AccessPoint(LocalStorage& config);
  virtual int8_t produce_data();
 protected:
  bool activate(bool retry) override;
  void deactivate() override;

 private:
  LocalStorage& _config;
};

#endif //BGEIGIECAST_ACCESS_POINT_SERVER_H_

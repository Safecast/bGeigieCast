//
// Created by Jelle Bouwhuis on 12/27/19.
//

#ifndef SENSOR_HANDLER_INCLUDE_ACTIVATABLE_HPP_
#define SENSOR_HANDLER_INCLUDE_ACTIVATABLE_HPP_

#include <Report.hpp>

class Aggregator;

/**
 * Some abstract class used by the receiver and observer
 */
class Activatable {
 public:
  Activatable() = default;

 protected:
  /**
   * Perform an activate function, will be called when set_active(true)
   * Override this when the data handler will be activated/deactivated in times. The deactivate can clean up.
   * Example, use of wifi or bluetooth connection
   * @return true if activate was success. if false, object will not be activated (and wont be used)
   */
  virtual bool activate(bool retry);

  /**
   * Perform an deactivate function, will be called when set_active(false)
   * Override this to cleanup the activation... shut down connections or other
   */
  virtual void deactivate();

 private:

  /**
   * Activates / deactivates the data handler. If the activate / deactivate fails, status wont change
   * Requires the data handler to be initialized
   * @param active: true to activate, false to deactivate
   */
  virtual void set_active(bool _activate, _Status& status) final;
  friend Aggregator;
};

#endif //SENSOR_HANDLER_INCLUDE_ACTIVATABLE_HPP_

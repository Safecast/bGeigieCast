#include <Arduino.h>

#include "i_api_connector.h"
#include "debugger.h"
#include "sm_a_process.h"

#define API_SEND(alert) (alert ? API_SEND_FREQUENCY_SECONDS_ALERT : API_SEND_FREQUENCY_SECONDS)
#define API_SEND_DEV(alert) (alert ? API_SEND_FREQUENCY_SECONDS_ALERT_DEV : API_SEND_FREQUENCY_SECONDS_DEV)
#define API_SEND_FREQUENCY(alert, dev, sped) (((dev && sped ? API_SEND_DEV(alert) : API_SEND(alert)) * 1000) - 2000)

IApiConnector::IApiConnector(IEspConfig& config, ApiConnectionObserver* observer) :
    _config(config),
    _saved_readings(),
    _last_send(0),
    _merged_reading(),
    _observer(observer),
    _alert(false){
}

bool IApiConnector::time_to_send() const {
  return millis() - _last_send > API_SEND_FREQUENCY(_alert, _config.get_use_dev(), _config.get_dev_sped_up());
}

void IApiConnector::init_reading_report(Reading* reading) {
  set_state(new ApiProcessReadingState(*this, reading));
}

void IApiConnector::process_reading(Reading* reading) {
  _merged_reading += *reading;
  if(time_to_send()) {
    _last_send = millis();
    if(_config.get_use_home_location()) {
      _merged_reading.apply_home_location(_config.get_home_latitude(), _config.get_home_longtitude());
    }
    if(_merged_reading.valid_reading()){
      schedule_event(e_a_report_reading);
    } else {
      // Invalid reading, no need to send this.
      schedule_event(e_a_not_reporting);
      _merged_reading.reset();
    }
  } else{
    schedule_event(e_a_not_reporting);
  }
}

void IApiConnector::save_reading(Reading* reading) {
  DEBUG_PRINTLN("Could not upload reading, trying again later");
  if(reading) {
    if(_saved_readings.get_count() == MAX_MISSED_READINGS) {
      // Delete oldest reading, else mem leak
      delete _saved_readings.get();
    }
    _saved_readings.add(new Reading(*reading));
  }
  schedule_event(e_a_reading_saved);
}

void IApiConnector::set_observer(ApiConnectionObserver* observer) {
  _observer = observer;
}

void IApiConnector::reset() {
  _last_send = millis();
  _merged_reading.reset();
}

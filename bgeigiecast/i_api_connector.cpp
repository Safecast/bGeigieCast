#include <Arduino.h>

#include "i_api_connector.h"
#include "debugger.h"
#include "sm_a_process.h"

#define API_SEND_FREQUENCY (API_SEND_FREQUENCY_MINUTES * 60 * 1000)
#define API_SEND_FREQUENCY_EMERGENCY (API_SEND_FREQUENCY_MINUTES_EMERGENCY * 60 * 1000)

IApiConnector::IApiConnector(IEspConfig& config, ApiConnectionObserver* observer) :
    _config(config),
    _saved_readings(),
    _last_send(0),
    _merged_reading(),
    _observer(observer),
    _emergency(false){
}

bool IApiConnector::time_to_send() const {
  return millis() - _last_send > (_emergency ? API_SEND_FREQUENCY_EMERGENCY : API_SEND_FREQUENCY);
}

void IApiConnector::init_reading_report(Reading* reading) {
  set_state(new ApiProcessReadingState(*this, reading));
}

void IApiConnector::process_reading(Reading* reading) {
  _merged_reading += *reading;
  if(time_to_send()) {
    _last_send = millis();
    schedule_event(e_a_report_reading);
  } else{
    schedule_event(e_a_not_reporting);
  }
}

void IApiConnector::save_reading(Reading* reading) {
  if(reading && reading->get_validity() == ReadingValidity::k_reading_valid) {
    DEBUG_PRINTLN("Could not upload reading, trying again later");
    if(_saved_readings.get_count() == MAX_MISSED_READINGS) {
      // Delete oldest reading, else mem leak
      delete _saved_readings.get();
    }
    _saved_readings.add(new Reading(*reading));
    schedule_event(e_a_reading_saved);
  }
}

void IApiConnector::set_observer(ApiConnectionObserver* observer) {
  _observer = observer;
}

void IApiConnector::reset() {
  _last_send = millis();
  _merged_reading.reset();
}

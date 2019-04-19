#include <Arduino.h>

#include "i_api_connector.h"
#include "debugger.h"
#include "sm_a_process.h"

#define API_SEND_FREQUENCY (API_SEND_FREQUENCY_MINUTES * 60 * 1000)
#define API_SEND_FREQUENCY_EMERGENCY (API_SEND_FREQUENCY_MINUTES_EMERGENCY * 60 * 1000)

IApiConnector::IApiConnector(IEspConfig& config) :
    _config(config),
    _saved_readings(),
    _last_send(0),
    _merged_reading(),
    _emergency(false){
}

bool IApiConnector::time_to_send() const {
  return millis() - _last_send > (_emergency ? API_SEND_FREQUENCY_EMERGENCY : API_SEND_FREQUENCY);
}

void IApiConnector::start_report_reading(Reading* reading) {
  set_state(new ApiProcessReadingState(*this, reading));
}

void IApiConnector::process_reading(Reading* reading) {
  _merged_reading += *reading;
  if(time_to_send()) {
    schedule_event(e_a_report_reading);
  } else{
    schedule_event(e_a_report_reading);
  }
  if(time_to_send()) {
    _last_send = millis();
    if(is_connected()) {
      while(!_saved_readings.empty()) {
        DEBUG_PRINTLN("Sending previously failed reading to API");
        Reading* past_reading = _saved_readings.get();
        send_reading(past_reading);
        delete past_reading;
      }
      DEBUG_PRINTLN("Sending latest reading to API");
      send_reading(reading);

    } else {
      // Save the reading to send it later
      save_reading(reading);
    }

    _merged_reading.reset();
  }
}

void IApiConnector::save_reading(Reading* reading) {
  DEBUG_PRINTLN("Could not upload reading, trying again later");
  if(_saved_readings.get_count() == MAX_MISSED_READINGS) {
    // Delete oldest reading, else mem leak
    delete _saved_readings.get();
  }
  _saved_readings.add(new Reading(*reading));
}

#include <Arduino.h>

#include "i_api_connector.h"
#include "debugger.h"

#define API_SEND_FREQUENCY (API_SEND_FREQUENCY_MINUTES * 60 * 1000)

IApiConnector::IApiConnector(IEspConfig& config) :
    config(config),
    missed_readings(),
    last_send(0),
    merged_reading() {
}

void IApiConnector::process_reading(Reading& reading) {
  merged_reading += reading;
  if(time_to_send()) {
    last_send = millis();
    if(is_connected()) {
      while(!missed_readings.empty()) {
        DEBUG_PRINTLN("Sending previously failed reading to API");
        Reading* past_reading = missed_readings.get();
        send_reading(*past_reading);
        delete past_reading;
      }
      DEBUG_PRINTLN("Sending latest reading to API");
      send_reading(reading);

    } else {
      // Save the reading to send it later
      save_reading(reading);
    }

    merged_reading.reset();
  }
}

bool IApiConnector::time_to_send() {
  return (millis() - last_send >= API_SEND_FREQUENCY);
}

void IApiConnector::save_reading(Reading& reading) {
  DEBUG_PRINTLN("Could not upload reading, trying again later");
  if(missed_readings.get_count() == MAX_MISSED_READINGS) {
    // Delete oldest reading, else mem leak
    delete missed_readings.get();
  }
  missed_readings.add(new Reading(reading));
}

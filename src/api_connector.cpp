#include "api_connector.h"
#include "debugger.h"

ApiConnector::ApiConnector(EspConfig& config) :
    config(config),
    missed_readings(),
    last_send(0),
    merged_reading() {
}

bool ApiConnector::start_connect() {
  if(is_connected()) {
    return true;
  }
  char ssid[32], password[32];
  if(!config.get_wifi_ssid(ssid)) {
    debug_println("No SSID to connect to!");
    return false;
  }

  config.get_wifi_password(password) ? WiFi.begin(ssid, password) : WiFi.begin(ssid);

  merged_reading.reset();
  return is_connected();
}

void ApiConnector::stop() {
  WiFi.disconnect(true, true);
}

bool ApiConnector::test() {
  WiFiClient client;
  return client.connect(API_PING_TEST_ADDRESS, 80) != 0;
}

bool ApiConnector::is_connected() {
  return WiFi.status() == WL_CONNECTED;
}

void ApiConnector::process_reading(Reading& reading) {
  debug_println("Adding new reading to merged_reading");
  merged_reading += reading;
  uint32_t now = millis();
  if(last_send + (API_SEND_FREQUENCY_MINUTES * 60) <= now) {
    if(is_connected()) {
      debug_println("Sending reading(s) to API");
      while(!missed_readings.empty()) {
        Reading* past_reading = missed_readings.get();
        send_reading(*past_reading);
        delete past_reading;
      }
      send_reading(reading);

    } else {
      debug_println("No API Connection saving it for later");
      // Save the reading to send it later
      save_reading(reading);
    }

    merged_reading.reset();
  }
}

void ApiConnector::save_reading(Reading& reading) {
  if(missed_readings.get_count() == MAX_MISSED_READINGS) {
    // Delete oldest reading, else mem leak
    delete missed_readings.get();
  }
  missed_readings.add(new Reading(reading));
}

bool ApiConnector::send_reading(Reading& reading) {
  //TODO: Send reading
  bool response = true;
  if(!response) {
    // Failed to send
    save_reading(reading);
  }
  return false;
}

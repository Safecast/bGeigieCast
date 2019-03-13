#include "api_connector.h"
#include "debugger.h"

#define API_SEND_FREQUENCY (API_SEND_FREQUENCY_MINUTES * 60 * 1000)

ApiConnector::ApiConnector(EspConfig& config) :
    config(config),
    missed_readings(),
    last_send(0),
    merged_reading() {
}

bool ApiConnector::start_connect(bool initial) {
  if(is_connected()) {
    return true;
  }

  const char* ssid = config.get_wifi_ssid();
  if(!ssid) {
    debug_println("No SSID to connect to!");
    return false;
  }

  if(initial) {
    const char* password = config.get_wifi_password();
    debug_print("Connecting to ssid "); debug_println(ssid);
    password ? WiFi.begin(ssid, password) : WiFi.begin(ssid);
    merged_reading.reset();
    last_send = millis();
  } else {
    WiFi.reconnect();
  }

  return is_connected();
}

void ApiConnector::stop() {
  WiFi.disconnect(true, true);
}

bool ApiConnector::test() {
  WiFiClient client;
  bool success = client.connect(API_HOST, 80) != 0;
  client.stop();
  return success;
}

bool ApiConnector::is_connected() {
  return WiFi.status() == WL_CONNECTED;
}

void ApiConnector::process_reading(Reading& reading) {
  merged_reading += reading;
  uint32_t now = millis();
  if(last_send + API_SEND_FREQUENCY <= now) {
    last_send = now;
    if(is_connected()) {
      while(!missed_readings.empty()) {
        debug_println("Sending previously failed reading to API");
        Reading* past_reading = missed_readings.get();
        send_reading(*past_reading);
        delete past_reading;
      }
      debug_println("Sending latest reading to API");
      send_reading(reading);

    } else {
      // Save the reading to send it later
      save_reading(reading);
    }

    merged_reading.reset();
  }
}

void ApiConnector::save_reading(Reading& reading) {
  debug_println("Could not upload reading, trying again later");
  if(missed_readings.get_count() == MAX_MISSED_READINGS) {
    // Delete oldest reading, else mem leak
    delete missed_readings.get();
  }
  missed_readings.add(new Reading(reading));
}

bool ApiConnector::send_reading(Reading& reading) {
  //TODO: Send reading
  char json_str[200];
  if(!reading.as_json(json_str)) {
    // This whole reading is invalid
    debug_println("Unable to send reading, its not valid at all!");
    return false;
  }
  HTTPClient http;

  char url[100];
  sprintf(url,
          "%s?api_key=%s&%s",
          API_MEASUREMENTS_ENDPOINT,
          config.get_api_key(),
          config.get_use_dev() ? "test=true" : "");

  //Specify destination for HTTP request
  if(!http.begin(url)) {
    debug_println("Unable to begin url connection");
    save_reading(reading);
    return false;
  }

  char content_length[5];

  sprintf(content_length, "%d", strlen(json_str));

  http.addHeader("Host", API_HOST);
  http.addHeader("Content-Type", HEADER_API_CONTENT_TYPE);
  http.addHeader("User-Agent", HEADER_API_USER_AGENT);
  http.addHeader("Content-Length", content_length);

  debug_println(url);
  debug_println(json_str);

  int httpResponseCode = http.POST(json_str);   //Send the actual POST request

  if(httpResponseCode > 0) {
    String response = http.getString();
    debug_print(httpResponseCode);
    debug_println(response);

    http.end();  //Free resources
    return true;
  } else {
    debug_println("Error on sending POST");
    // Failed to send
    save_reading(reading);

    http.end();  //Free resources
    return false;
  }
}

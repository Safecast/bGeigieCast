
#include "api_connector.h"
#include "debugger.h"
#include "identifiers.h"

#define API_SEND(alert) (alert ? API_SEND_FREQUENCY_SECONDS_ALERT : API_SEND_FREQUENCY_SECONDS)
#define API_SEND_DEV(alert) (alert ? API_SEND_FREQUENCY_SECONDS_ALERT_DEV : API_SEND_FREQUENCY_SECONDS_DEV)
#define API_SEND_FREQUENCY(alert, dev) (((dev ? API_SEND_DEV(alert) : API_SEND(alert)) * 1000) - 2000)

ApiReporter::ApiReporter(LocalStorage& config) :
    Handler(k_handler_api_reporter),
    _config(config),
    _saved_readings(),
    _last_send(),
    _merged_reading(),
    _current_default_response(e_api_reporter_idle),
    _alert() {
}

bool ApiReporter::is_connected() const {
  return WiFi.status() == WL_CONNECTED;
}

bool ApiReporter::time_to_send() const {
  return millis() - _last_send > API_SEND_FREQUENCY(_alert, _config.get_use_dev());
}

void ApiReporter::save_reading() {
  DEBUG_PRINTLN("Could not upload reading, trying again later");
  if(_merged_reading.valid_reading()) {
    _saved_readings.add(_merged_reading);
  }
}

void ApiReporter::reset() {
  _last_send = millis();
  _merged_reading.reset();
}

bool ApiReporter::activate(bool retry) {
  if(is_connected()) {
    return true;
  }

  if(retry) {
    WiFi.reconnect();
  } else {
    const char* ssid = _config.get_wifi_ssid();
    if(!ssid) {
      DEBUG_PRINTLN("No SSID to connect to!");
      return false;
    }
    const char* password = _config.get_wifi_password();
    DEBUG_PRINT("Connecting to ssid ");
    DEBUG_PRINTLN(ssid);
    password ? WiFi.begin(ssid, password) : WiFi.begin(ssid);
  }

  return is_connected();
}

void ApiReporter::deactivate() {
  reset();
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_MODE_NULL);
}

int8_t ApiReporter::handle_produced_work(const worker_status_t& worker_reports) {
  const auto& reader = worker_reports.at(k_worker_bgeigie_connector);
  if(!reader.is_fresh()) {
    return _current_default_response;
  }
  const auto& reading = reader.get<Reading>();
  _merged_reading += reading;
  if(!time_to_send()) {
    return _current_default_response;
  }

  _last_send = millis();
  if(_config.get_use_home_location()) {
    _merged_reading.apply_home_location(_config.get_home_latitude(), _config.get_home_longitude());
  }

  if(_merged_reading.valid_reading()) {
    _current_default_response = send_reading(reading);
  } else {
    return e_api_reporter_error_invalid_reading;
  }
  reset();
}

ApiReporter::ApiHandlerStatus ApiReporter::send_reading(const Reading& reading) {
  char json_str[200];
  if(!_merged_reading.as_json(json_str)) {
    // This whole reading is invalid
    DEBUG_PRINTLN("Unable to send reading, its not valid at all!");
    return e_api_reporter_error_invalid_reading;
  }

  if(!is_connected() && !activate(true)) {
    DEBUG_PRINTLN("Unable to send, lost connection");
    return e_api_reporter_error_not_connected;
  }

  HTTPClient http;

  char url[100];
  sprintf(url,
          "%s?api_key=%s&%s",
          API_MEASUREMENTS_ENDPOINT,
          _config.get_api_key(),
          _config.get_use_dev() ? "test=true" : "");

  //Specify destination for HTTP request
  if(!http.begin(url)) {
    DEBUG_PRINTLN("Unable to begin url connection");
    http.end();  //Free resources
    return e_api_reporter_error_remote_not_available;
  }

  char content_length[5];

  sprintf(content_length, "%d", strlen(json_str));

  http.addHeader("Host", API_HOST);
  http.addHeader("Content-Type", HEADER_API_CONTENT_TYPE);
  http.addHeader("User-Agent", HEADER_API_USER_AGENT);
  http.addHeader("Content-Length", content_length);

  DEBUG_PRINTLN(url);
  DEBUG_PRINTLN(json_str);

  int httpResponseCode = http.POST(json_str);   //Send the actual POST request

  if(httpResponseCode >= 200 && httpResponseCode < 300) {
    String response = http.getString();
    DEBUG_PRINTLN("POST successfull");
    DEBUG_PRINT(httpResponseCode);
    DEBUG_PRINTLN(response);
    http.end();  //Free resources
    return e_api_reporter_send_success;
  } else if(httpResponseCode > 0) {
    DEBUG_PRINTLN("Remote error on sending POST");
    http.end();  //Free resources
    return e_api_reporter_error_server_rejected_post;
  } else {
    DEBUG_PRINTLN("Remote not available");
    http.end();  //Free resources
    // Failed to send
    return e_api_reporter_error_remote_not_available;

  }
}

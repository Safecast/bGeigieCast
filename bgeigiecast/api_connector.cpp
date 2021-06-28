
#include "api_connector.h"
#include "debugger.h"
#include "identifiers.h"
#include "bgeigie_connector.h"

#define RETRY_TIMEOUT 10000

// subtracting 1 seconds so data is send more often than not.
#define SEND_FREQUENCY(last_send, sec) (millis() - last_send > ((sec * 1000) - 1000))

ApiConnector::ApiConnector(LocalStorage& config) :
    Handler(),
    _config(config),
//    _reading_buffer(),
    _last_send(),
    _current_default_response(e_api_reporter_idle),
    _alert() {
}

bool ApiConnector::time_to_send() const {
  switch(static_cast<SendFrequency>(_config.get_send_frequency())) {
    case e_api_send_frequency_5_sec:
      return SEND_FREQUENCY(_last_send, 5);
    case e_api_send_frequency_1_min:
      return SEND_FREQUENCY(_last_send, 60);
    case e_api_send_frequency_5_min:
    default:  // Default 5 min frequency
      return SEND_FREQUENCY(_last_send, 5 * 60);
  }
}

bool ApiConnector::activate(bool retry) {
  static uint32_t last_try = 0;
  if(WiFiConnection::wifi_connected()) {
    return true;
  }
  if(retry && millis() - last_try < RETRY_TIMEOUT) {
    return false;
  }
  last_try = millis();

  WiFiConnection::connect_wifi(_config.get_wifi_ssid(), _config.get_wifi_password());

  return WiFi.isConnected();
}

void ApiConnector::deactivate() {
  _current_default_response = e_api_reporter_idle;
  WiFiConnection::disconnect_wifi();
}

int8_t ApiConnector::handle_produced_work(const worker_map_t& workers) {
  const auto& geigie_connector = workers.worker<BGeigieConnector>(k_worker_bgeigie_connector);

  if(!geigie_connector || !geigie_connector->is_fresh()) {
    // No fresh data
    DEBUG_PRINTLN("no fresh data");
    return _current_default_response;
  }

  if(!time_to_send()) {
    DEBUG_PRINTLN("not time to send");
    return _current_default_response;
  }

  _last_send = millis();

  const auto& reading = geigie_connector->get_data();

  if(reading.valid_reading()) {
    if (_config.get_use_home_location() && !reading.near_location(_config.get_home_latitude(), _config.get_home_longitude())) {
      // Reading not near home location
      DEBUG_PRINTLN("not time to send");
      return _current_default_response;
    }
    _current_default_response = send_reading(reading);
  }
  return _current_default_response;
}

ApiConnector::ApiHandlerStatus ApiConnector::send_reading(const Reading& reading) {

  if(!WiFi.isConnected() && !activate(true)) {
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

  char payload[200];

  if(!reading_to_json(reading, payload)) {
    return e_api_reporter_error_to_json;
  }

  char content_length[5];

  sprintf(content_length, "%d", strlen(payload));

  http.addHeader("Host", API_HOST);
  http.addHeader("Content-Type", HEADER_API_CONTENT_TYPE);
  http.addHeader("User-Agent", HEADER_API_USER_AGENT);
  http.addHeader("Content-Length", content_length);

  int httpResponseCode = http.POST(payload);

  String response = http.getString();
  DEBUG_PRINTF("POST complete, status %d\r\nrepsonse: \r\n\r\n%s\r\n\r\n", httpResponseCode, response.c_str());
  http.end();  //Free resources

  switch(httpResponseCode) {
    case 201:
      DEBUG_PRINTLN("POST successfull");
      DEBUG_PRINT(httpResponseCode);
      DEBUG_PRINTLN(response);
      return e_api_reporter_send_success;
    case 400:
      return e_api_reporter_error_server_rejected_post_400;
    case 401:
      return e_api_reporter_error_server_rejected_post_401;
    case 403:
      return e_api_reporter_error_server_rejected_post_403;
    case 500 ... 599:
      return e_api_reporter_error_server_rejected_post_5xx;
    default:
      return e_api_reporter_error_remote_not_available;
  }

}

bool ApiConnector::reading_to_json(const Reading& reading, char* out) {
  if(!reading.valid_reading()) {
    return false;
  }

  sprintf(
      out,
      "{\"captured_at\":\"%s\","
      "\"device_id\":%d,"
      "\"value\":%d,"
      "\"unit\":\"cpm\","
      "\"longitude\":%.5f,"
      "\"latitude\":%.5f}\n",
      reading.get_iso_timestamp(),
      reading.get_fixed_device_id(),
      reading.get_cpm(),
      _config.get_use_home_location() ? _config.get_home_longitude() : reading.get_longitude(),
      _config.get_use_home_location() ? _config.get_home_latitude() : reading.get_latitude()
  );
  return true;
}


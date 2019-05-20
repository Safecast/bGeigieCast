
#include "api_connector.h"
#include "debugger.h"

ApiConnector::ApiConnector(IEspConfig& config, ApiConnectionObserver* observer) : IApiConnector(config, observer) {
}

bool ApiConnector::start_connect() {
  switch(WiFi.status()) {
    case WL_CONNECTED:
      schedule_event(e_a_wifi_connected);
      return true;
    case WL_IDLE_STATUS:
    case WL_DISCONNECTED:
      WiFi.reconnect();
      break;
    default:
      perform_connect();
      break;
  }

  return false;
}

void ApiConnector::disconnect() {
  WiFi.disconnect();
}

void ApiConnector::stop() {
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_MODE_NULL);
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

bool ApiConnector::send_reading(Reading* reading) {
  DEBUG_PRINTLN("Sending reading to API");
  char json_str[200];
  if(!reading->as_json(json_str)) {
    // This whole reading is invalid
    DEBUG_PRINTLN("Unable to send reading, its not valid at all!");
    schedule_event(e_a_api_post_failed);
    return false;
  }

  if(!is_connected()) {
    DEBUG_PRINTLN("Unable to send, lost connection");
    schedule_event(e_a_api_post_failed);
    return false;
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
    save_reading(reading);
    http.end();  //Free resources
    return false;
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

  if(httpResponseCode > 0) {
    String response = http.getString();
    DEBUG_PRINT(httpResponseCode);
    DEBUG_PRINTLN(response);
    schedule_event(e_a_reading_posted);
    http.end();  //Free resources
    return true;
  } else {
    DEBUG_PRINTLN("Error on sending POST");
    // Failed to send
    schedule_event(e_a_api_post_failed);
    http.end();  //Free resources
    return false;
  }
}

void ApiConnector::perform_connect() {

  const char* ssid = _config.get_wifi_ssid();
  if(!ssid) {
    DEBUG_PRINTLN("No SSID to connect to!");
    return;
  }

  const char* password = _config.get_wifi_password();
  DEBUG_PRINT("Connecting to ssid ");
  DEBUG_PRINTLN(ssid);
  password ? WiFi.begin(ssid, password) : WiFi.begin(ssid);
}

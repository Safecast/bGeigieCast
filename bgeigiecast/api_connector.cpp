
#include <IPAddress.h>
#include "api_connector.h"
#include "debugger.h"

ApiConnector::ApiConnector(IEspConfig& config, ApiConnectionObserver* observer) : IApiConnector(config, observer),
                                                                                  _api_endpoint(INADDR_NONE) {
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

bool ApiConnector::retrieve_endpoint() {
  if(WiFi.hostByName(API_HOST, _api_endpoint)) {
    schedule_event(e_a_endpoint_available);
    return true;
  }
  schedule_event(e_a_endpoint_unavailable);
  return false;
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
          "http://%s%s?api_key=%s&%s",
          _api_endpoint.toString().c_str(),
          API_MEASUREMENTS_ENDPOINT,
          _config.get_api_key(),
          _config.get_use_dev() ? "test=true" : "");

  //Specify destination for HTTP request
  if(!http.begin(url)) {
    DEBUG_PRINTLN("Unable to begin url connection");
    schedule_event(e_a_api_post_failed);
    http.end();  //Free resources
    return false;
  }

  http.addHeader("Host", API_HOST);
  http.addHeader("Content-Type", HEADER_API_CONTENT_TYPE);
  http.setUserAgent(HEADER_API_USER_AGENT);

  DEBUG_PRINTLN(url);
  DEBUG_PRINTLN(json_str);

  int httpResponseCode = http.POST(json_str);   //Send the actual POST request

  DEBUG_PRINTF("Response code: %d\n", httpResponseCode);

  bool ret = false;

  if(httpResponseCode == 200 || httpResponseCode == 201) {
    String response = http.getString();
    DEBUG_PRINTLN(response);
    schedule_event(e_a_reading_posted);
    ret = true;
  }else {
    if(httpResponseCode == -1 && api_endpoint_resolved()) {
      // Connection to server could not be made
      _api_endpoint = INADDR_NONE;
    }
    schedule_event(e_a_api_post_failed);
  }

  http.end();  //Free resources
  return ret;
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

bool ApiConnector::api_endpoint_resolved() const {
  return !(_api_endpoint == INADDR_NONE);
}

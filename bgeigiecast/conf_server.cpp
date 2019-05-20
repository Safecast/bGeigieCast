#include "conf_server.h"
#include "user_config.h"
#include "esp_config.h"
#include "debugger.h"
#include "http_responses.h"
#include "http_pages.h"


template<typename T>
T clamp(T val, T min, T max) {
  return val < min ? min : val > max ? max : val;
}

ConfigWebServer::ConfigWebServer(IEspConfig& config) : _server(SERVER_WIFI_PORT), _config(config) {
  set_endpoints();
}

bool ConfigWebServer::initialize() {
  if(!_config.get_device_id() || !_config.get_ap_password()) {
    DEBUG_PRINTLN("No SSID or password to start config server");
    return false;
  }
  char ssid[16];
  sprintf(ssid, ACCESS_POINT_SSID, _config.get_device_id());
  WiFi.softAP((ssid), _config.get_ap_password());

  delay(100);

  IPAddress ip(ACCESS_POINT_IP);
  IPAddress n_mask(ACCESS_POINT_NMASK);
  WiFi.softAPConfig(ip, ip, n_mask);

  delay(100);

  _server.begin();
  return true;
}

void ConfigWebServer::stop() {
  _server.stop();
  WiFi.softAPdisconnect(true);
}

void ConfigWebServer::handle_requests() {
  _server.handleClient();
}


void ConfigWebServer::handle_client_request(Stream& client, HttpRequest& request) {
  if(request.is_uri("/")) {

    respondSuccess(client, transmission_buffer);

  } else if(request.is_uri("/save")) {

    char value[64];
    if(request.get_param_value("ap_password", value, 64)) {
      _config.set_ap_password(value, false);
    }
    if(request.get_param_value("wf_ssid", value, 64)) {
      _config.set_wifi_ssid(value, false);
    }
    if(request.get_param_value("wf_password", value, 64)) {
      _config.set_wifi_password(value, false);
    }
    if(request.get_param_value("apikey", value, 64)) {
      _config.set_api_key(value, false);
    }
    if(request.get_param_value("devsrv", value, 64)) {
      _config.set_use_dev(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("devfreq", value, 64)) {
      _config.set_dev_sped_up(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("led_intensity", value, 64)) {
      _config.set_led_color_intensity(clamp<uint8_t>(static_cast<uint8_t>(strtoul(value, nullptr, 10)), 5, 100), false);
    }
    if(request.get_param_value("led_color", value, 64)) {
      _config.set_led_color_blind(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("use_home_loc", value, 64)) {
      _config.set_use_home_location(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("home_lat", value, 64)) {
      _config.set_home_latitude(clamp<double>(strtod(value, nullptr), -90.0, 90.0), false);
    }
    if(request.get_param_value("home_long", value, 64)) {
      _config.set_home_longitude(clamp<double>(strtod(value, nullptr), -180.0, 180.0), false);
    }

    respondRedirect(client, "/?success=true");

  } else {

    respondNotFound(client);

  }
}
void ConfigWebServer::set_endpoints() {
  // Root
  _server.on("/", HTTP_GET, [this](){
    _server.uri();
    sprintf(
        transmission_buffer
        ,config_response_format
        ,request.has_param("success") ? "<em>Configurations saved!</em> - <a href=\"/\">OK</a><br>" : ""
        ,_config.get_device_id()
        ,_config.get_ap_password()
        ,_config.get_wifi_ssid()
        ,_config.get_wifi_password()
        ,_config.get_api_key()
        ,_config.get_use_dev() ? "checked" : ""
        ,_config.get_use_dev() ? "" : "checked"
        ,_config.get_dev_sped_up() ? "" : "checked"
        ,_config.get_dev_sped_up() ? "checked" : ""
        ,_config.get_led_color_intensity()
        ,_config.is_led_color_blind() ? "" : "checked"
        ,_config.is_led_color_blind() ? "checked" : ""
        ,_config.get_use_home_location() ? "" : "checked"
        ,_config.get_use_home_location() ? "checked" : ""
        ,_config.get_home_latitude()
        ,_config.get_home_longtitude()
        ,_config.get_last_latitude()
        ,_config.get_last_longtitude()
    );

  });

  // Save
  _server.on("/save", HTTP_GET, [](){});

}

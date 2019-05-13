#include "conf_server.h"
#include "user_config.h"
#include "esp_config.h"
#include "debugger.h"
#include "http_responses.h"

typedef enum {
  request_line,
  header,
  content
} RequestParse;

ConfigWebServer::ConfigWebServer(IEspConfig& config) : server(SERVER_WIFI_PORT, SERVER_MAX_CLIENTS), config(config) {
}

bool ConfigWebServer::initialize() {
  if(!config.get_device_id() || !config.get_ap_password()) {
    DEBUG_PRINTLN("No SSID or password to start config server");
    return false;
  }
  char ssid[16];
  sprintf(ssid, ACCESS_POINT_SSID, config.get_device_id());
  WiFi.softAP((ssid), config.get_ap_password());

  delay(100);

  IPAddress ip(ACCESS_POINT_IP);
  IPAddress n_mask(ACCESS_POINT_NMASK);
  WiFi.softAPConfig(ip, ip, n_mask);

  delay(100);

  server.begin();
  return is_running();
}

void ConfigWebServer::stop() {
  server.stop();
  WiFi.softAPdisconnect(true);
}

void ConfigWebServer::handle_requests() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if(client) {                             // If a new client connects,
    DEBUG_PRINTLN("New Client.");          // print a message out in the serial port
    HttpRequest request;
    RequestParse state = RequestParse::request_line;
    String currentLine = "";

    while(client.connected()) {
      if(client.available()) {
        char c = static_cast<char>(client.read());
        switch(c) {
          case '\r':
            break;
          case '\n': {
            switch(state) {
              case request_line:
                request.set_request_line(currentLine.c_str());
                state = RequestParse::header;
                currentLine = "";
                break;
              case header:
                if(currentLine != "") {
                  request.add_header_line(currentLine.c_str());
                  currentLine = "";
                } else {
                  state = RequestParse::content;
                }
                break;
              case content:
                break;
            }
            break;
          }
          default:
            currentLine += c;
            break;
        }
      }
      if(state == RequestParse::content) {
        handle_client_request(client, request);
        break;
      }
    }
    // Close the connection
    client.stop();
    DEBUG_PRINTLN("Client disconnected.");
  }
}

bool ConfigWebServer::is_running() {
  return !!server;
}


void ConfigWebServer::handle_client_request(Stream& client, HttpRequest& request) {
  if(request.is_uri("/")) {
    char transmission[4096];

    sprintf(
        transmission,
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<link rel='icon' href='data:image/x-icon;base64,AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAA"
        "AAgAAAAAAAAAAAAAAAEAAAAAAAAACAhYcA////AA0PEAC+pm4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAIiIiIiIiIiIiIiIiIiIiIiIiMyISESIiIiIzIhIRIiIiIiIiEhEiIiIiIiISESIiIiIiIRIRIiIiIiIRIhEiIiIiERIi"
        "ESIiIiIQIhESIiIiIiIRESIiIiIiEREiIiIiIiIRIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' type='image/x-png' />"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        "<style>body {font-family: Helvetica; text-align: center;} form {background-color: lightgrey; text-align: left; margin: 20px; padding: 20px;} input[type=\"text\"], input[type=\"number\"] {max-width: 300px; width: 95%%; padding: 3px; border-radius: 8px; margin-bottom: 5px;}, </style>"
        "</head>"
        "<body>"
        "%s"
        "<strong>Config Page</strong><br>"
        "BgeigieCast %d<br>"
        "<form action=\"save\" method=\"get\" > "
        "bGeigieCast password:<br><input type=\"text\" name=\"ap_password\" value=\"%s\"><br>"
        "Network wifi ssid:<br><input type=\"text\" name=\"wf_ssid\" value=\"%s\"><br>"
        "Network wifi password:<br><input type=\"text\" name=\"wf_password\" value=\"%s\"><br>"
        "Safecast API key:<br><input type=\"text\" name=\"apikey\" value=\"%s\"><br>"
        "Use safecast server:<br>"
        "<input type=\"radio\" name=\"devsrv\" value=\"1\" %s>Development<br>"
        "<input type=\"radio\" name=\"devsrv\" value=\"0\" %s>Production<br>"
        "<hr>"
        "LED intensity:<br><input type=\"number\" min=\"0\" max=\"255\" name=\"led_intensity\" value=\"%d\"><br>"
        "LED Colors:<br>"
        "<input type=\"radio\" name=\"led_color\" value=\"0\" %s>Default<br>"
        "<input type=\"radio\" name=\"led_color\" value=\"1\" %s>Color blind<br>"
        "<hr>"
        "Fixed mode GPS settings:<br>"
        "<input type=\"radio\" name=\"use_home_loc\" value=\"0\" %s>Use home location<br>"
        "<input type=\"radio\" name=\"use_home_loc\" value=\"1\" %s>Use GPS<br>"
        "Home latitude:<br><input type=\"number\" min=\"-90.0000\" max=\"90.0000\" name=\"home_lat\" id=\"home_lat\" value=\"%.4f\" step=\"0.0001\"><br>"
        "Home longitude:<br><input type=\"number\" min=\"-180.0000\" max=\"180.0000\" name=\"home_long\" id=\"home_long\" value=\"%.4f\" step=\"0.0001\"><br>"
        "Last known location: (<a href=\"#\" onclick=\""
        "document.getElementById('home_lat').value = document.getElementById('last_lat').innerHTML;"
        "document.getElementById('home_long').value = document.getElementById('last_long').innerHTML;"
        "return false;"
        "\">Use this</a>)<br>"
        "Latitude: <span id=\"last_lat\">%.4f</span><br>"
        "Longitude: <span id=\"last_long\">%.4f</span><br>"
        "<input type=\"submit\" value=\"Submit\" style=\"background-color: #FF9800; font-size: initial;color: white;\">"
        "</form><br><br>"
        "</body>"
        "</html>"
        ,request.has_param("success") ? "<em>Configurations saved!</em> - <a href=\"/\">OK</a><br>" : ""
        ,config.get_device_id()
        ,config.get_ap_password()
        ,config.get_wifi_ssid()
        ,config.get_wifi_password()
        ,config.get_api_key()
        ,config.get_use_dev() ? "checked" : ""
        ,config.get_use_dev() ? "" : "checked"
        ,config.get_led_color_intensity()
        ,config.is_led_color_blind() ? "" : "checked"
        ,config.is_led_color_blind() ? "checked" : ""
        ,config.get_use_home_location() ? "" : "checked"
        ,config.get_use_home_location() ? "checked" : ""
        ,config.get_home_latitude()
        ,config.get_home_longtitude()
        ,config.get_last_latitude()
        ,config.get_last_longtitude()
    );
    respondSuccess(client, transmission);

  } else if(request.is_uri("/save")) {

    char value[64];
    if(request.get_param_value("ap_password", value, 64)) {
      config.set_ap_password(value, false);
    }
    if(request.get_param_value("wf_ssid", value, 64)) {
      config.set_wifi_ssid(value, false);
    }
    if(request.get_param_value("wf_password", value, 64)) {
      config.set_wifi_password(value, false);
    }
    if(request.get_param_value("apikey", value, 64)) {
      config.set_api_key(value, false);
    }
    if(request.get_param_value("devsrv", value, 64)) {
      config.set_use_dev(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("led_intensity", value, 64)) {
      config.set_led_color_intensity(static_cast<uint8_t>(strtoul(value, nullptr, 10)), false);
    }
    if(request.get_param_value("led_color", value, 64)) {
      config.set_led_color_blind(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("use_home_loc", value, 64)) {
      config.set_use_home_location(strcmp(value, "1") == 0, false);
    }
    if(request.get_param_value("home_long", value, 64)) {
      config.set_home_longitude(strtod(value, nullptr), false);
    }
    if(request.get_param_value("home_lat", value, 64)) {
      config.set_home_latitude(strtod(value, nullptr), false);
    }

    respondRedirect(client, "/?success=true");

  } else {

    respondNotFound(client);

  }
}

#include <Update.h>
#include <ESPmDNS.h>
#include "conf_server.h"
#include "user_config.h"
#include "esp_config.h"
#include "debugger.h"
#include "http_pages.h"

template<typename T, typename T2>
T clamp(T2 val, T min, T max) {
  T _val = static_cast<T>(val);
  return _val < min ? min : _val > max ? max : _val;
}

ConfigWebServer::ConfigWebServer(IEspConfig& config) : _server(SERVER_WIFI_PORT), _config(config) {
}

bool ConfigWebServer::initialize() {
  auto device_id = _config.get_device_id();

  if(!_config.get_device_id() || !_config.get_ap_password()) {
    DEBUG_PRINTLN("Can't start config without device id!");
    return false;
  }

  char host_ssid[16];
  device_id ? sprintf(host_ssid, ACCESS_POINT_SSID "%d", device_id) : sprintf(host_ssid, ACCESS_POINT_SSID "unknown");

  MDNS.begin(host_ssid);

  delay(100);

  if(_config.get_wifi_ssid()) {
    for(int i = 0; i < 3; ++i) {
      connect_wifi();

      auto time = millis();
      while(millis() - time < 2000) {
        if(WiFi.status() == WL_CONNECTED) {

          DEBUG_PRINTF("Connected to %s, IP address: %s\n", _config.get_wifi_ssid(), WiFi.localIP().toString().c_str());

          set_endpoints();
          _server.begin();
          return true;
        }
      }
    }

    WiFi.disconnect(true, true);
  }

  if(start_ap_server(host_ssid)) {
    set_endpoints();
    _server.begin();
    return true;
  }
  return false;
}

void ConfigWebServer::stop() {
  _server.stop();
  WiFi.softAPdisconnect(true);
}

void ConfigWebServer::handle_requests() {
  _server.handleClient();
}

bool ConfigWebServer::connect_wifi() {
  switch(WiFi.status()) {
    case WL_CONNECTED:
      return true;
    case WL_IDLE_STATUS:
    case WL_DISCONNECTED:
      WiFi.reconnect();
      return false;
    default:
      const char* wifi_ssid = _config.get_wifi_ssid();
      const char* password = _config.get_wifi_password();
      password ? WiFi.begin(wifi_ssid, password) : WiFi.begin(wifi_ssid);
      return false;
  }
}

bool ConfigWebServer::start_ap_server(const char* host_ssid) {

  WiFi.softAP(host_ssid, _config.get_ap_password());
  delay(100);

  IPAddress ip(ACCESS_POINT_IP);
  IPAddress n_mask(ACCESS_POINT_NMASK);
  WiFi.softAPConfig(ip, ip, n_mask);

  delay(100);

  return true;
}

void ConfigWebServer::set_endpoints() {
  // Home
  _server.on("/", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_home_page());
  });

  // Configure Device
  _server.on("/configure/device", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_config_device_page(
        _server.hasArg("success"),
        _config.get_device_id(),
        _config.get_led_color_intensity(),
        _config.is_led_color_blind()
    ));
  });

  // Configure Connection
  _server.on("/configure/connection", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_config_network_page(
        _server.hasArg("success"),
        _config.get_device_id(),
        _config.get_ap_password(),
        _config.get_wifi_ssid(),
        _config.get_wifi_password(),
        _config.get_api_key(),
        _config.get_use_dev(),
        _config.get_dev_sped_up()
    ));
  });

  // Configure Location
  _server.on("/configure/location", HTTP_GET, [this]() {

    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_config_location_page(
        _server.hasArg("success"),
        _config.get_device_id(),
        _config.get_use_home_location() ,
        _config.get_home_latitude(),
        _config.get_home_longtitude(),
        _config.get_last_latitude(),
        _config.get_last_longtitude()
    ));

    _server.sendHeader("Connection", "close");
  });

  // Save config
  _server.on("/configure/save", HTTP_POST, [this]() {
    handle_save();
  });

  // Upload get
  _server.on("/update", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_upload_page());
  });

  // Upload post
  _server.on("/update", HTTP_POST, [this]() {
    // Complete
    _server.sendHeader("Connection", "close");
    if(_server.upload().totalSize == 0 || Update.hasError()) {
      _server.send(200, "text/plain", "FAIL");
    }
    else {
      _server.send(200, "text/plain", "OK");
      _server.client().flush();
      ESP.restart();
    }
  }, [this]() {
    // Upload progress
    handle_update_uploading();
  });

  // Other things
  _server.on("/configure", [this]() { // Redirect
    _server.sendHeader("Location", "/configure/device");
    _server.send(302);
  });

}

void ConfigWebServer::handle_save() {
  if(_server.hasArg("ap_password")) {
    _config.set_ap_password(_server.arg("ap_password").c_str(), false);
  }
  if(_server.hasArg("wf_ssid")) {
    _config.set_wifi_ssid(_server.arg("wf_ssid").c_str(), false);
  }
  if(_server.hasArg("wf_password")) {
    _config.set_wifi_password(_server.arg("wf_password").c_str(), false);
  }
  if(_server.hasArg("apikey")) {
    _config.set_api_key(_server.arg("apikey").c_str(), false);
  }
  if(_server.hasArg("devsrv")) {
    _config.set_use_dev(_server.arg("devsrv") == "1", false);
  }
  if(_server.hasArg("devfreq")) {
    _config.set_dev_sped_up(_server.arg("devfreq") == "1", false);
  }
  if(_server.hasArg("led_intensity")) {
    _config.set_led_color_intensity(clamp<uint8_t>(_server.arg("led_intensity").toInt(), 5, 100), false);
  }
  if(_server.hasArg("led_color")) {
    _config.set_led_color_blind(strcmp(_server.arg("wf_ssid").c_str(), "1") == 0, false);
  }
  if(_server.hasArg("use_home_loc")) {
    _config.set_use_home_location(strcmp(_server.arg("wf_ssid").c_str(), "1") == 0, false);
  }
  if(_server.hasArg("home_lat")) {
    _config.set_home_latitude(clamp<double>(_server.arg("home_lat").toDouble(), -90.0, 90.0), false);
  }
  if(_server.hasArg("home_long")) {
    _config.set_home_longitude(clamp<double>(_server.arg("home_long").toDouble(), -180.0, 180.0), false);
  }

  _server.sendHeader("Location", _server.header("Referer") + "?success=true");
  _server.send(302, "text/html");
  _server.client().flush();
}

void ConfigWebServer::handle_update_uploading() {
  HTTPUpload& upload = _server.upload();
  switch(upload.status) {
    case UPLOAD_FILE_START: {
      DEBUG_PRINTF("Update: %s\n", upload.filename.c_str());
      Update.begin(UPDATE_SIZE_UNKNOWN) ? DEBUG_PRINTLN("Starting update") : DEBUG_PRINTLN("Unable to start update");
      break;
    }
    case UPLOAD_FILE_WRITE: {
      DEBUG_PRINTF(".");
      auto write_size = Update.write(upload.buf, upload.currentSize);
      if(write_size != upload.currentSize) {
        DEBUG_PRINTF("Something failed while uploading (wrote %d out of %d)\n", write_size, upload.currentSize);
      }
      break;
    }
    case UPLOAD_FILE_END: {
      if(upload.totalSize > 0 && Update.end(true)) { //true to set the size to the current progress
        DEBUG_PRINTF("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        DEBUG_PRINTF("Update Failed...");
      }
      break;
    }
    case UPLOAD_FILE_ABORTED: {
      Update.abort();
      DEBUG_PRINTF("Update aborted...");
      break;
    }
  }
}

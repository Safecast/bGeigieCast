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
  sprintf(host_ssid, ACCESS_POINT_SSID, device_id);

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
          HttpPages::internet_access = true;
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
    _server.send(200, "text/html", HttpPages::get_home_page(_config.get_device_id()));
  });

  // Configure Device
  _server.on("/device", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_config_device_page(
        _server.hasArg("success"),
        _config.get_device_id(),
        _config.get_led_color_intensity(),
        _config.is_led_color_blind()
    ));
  });

  // Configure Connection
  _server.on("/connection", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_config_connection_page(
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
  _server.on("/location", HTTP_GET, [this]() {

    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_config_location_page(
        _server.hasArg("success"),
        _config.get_device_id(),
        _config.get_use_home_location() ,
        _config.get_home_latitude(),
        _config.get_home_longitude(),
        _config.get_last_latitude(),
        _config.get_last_longitude()
    ));

    _server.sendHeader("Connection", "close");
  });

  // Save config
  _server.on("/save", HTTP_POST, [this]() {
    handle_save();
  });

  // Upload get
  _server.on("/update", HTTP_GET, [this]() {
    _server.sendHeader("Connection", "close");
    _server.send(200, "text/html", HttpPages::get_update_page(_config.get_device_id()));
  });

  // Upload post
  _server.on("/update", HTTP_POST, [this]() {
    // Complete
    _server.sendHeader("Connection", "close");
    if(_server.upload().totalSize == 0 || Update.hasError()) {
      _server.send(500, "text/plain", "FAIL");
    }
    else {
      _server.send(200, "text/plain", "OK");
      _server.client().flush();
    }
  }, [this]() {
    // Progress
    handle_update_uploading();
  });

  _server.on("/reboot", [this]() { // Reboot
    ESP.restart();
  });

  // css get
  _server.on("/pure.css", HTTP_GET, [this]() {
    _server.sendHeader("Content-Encoding", "gzip");
    _server.send_P(200, "text/css", reinterpret_cast<const char*>(HttpPages::pure_css), PURE_CSS_SIZE);
  });

  // css get
  _server.on("/favicon.ico", HTTP_GET, [this]() {
    _server.send_P(200, "image/x-icon", reinterpret_cast<const char*>(HttpPages::favicon), FAVICON_SIZE);
  });

}

void ConfigWebServer::handle_save() {
  if(_server.hasArg("c_ap")) {
    _config.set_ap_password(_server.arg("c_ap").c_str(), false);
  }
  if(_server.hasArg("c_ws")) {
    _config.set_wifi_ssid(_server.arg("c_ws").c_str(), false);
  }
  if(_server.hasArg("c_wp")) {
    _config.set_wifi_password(_server.arg("c_wp").c_str(), false);
  }
  if(_server.hasArg("c_ak")) {
    _config.set_api_key(_server.arg("c_ak").c_str(), false);
  }
  if(_server.hasArg("c_ud")) {
    _config.set_use_dev(_server.arg("c_ud") == "1", false);
  }
  if(_server.hasArg("c_df")) {
    _config.set_dev_sped_up(_server.arg("c_df") == "1", false);
  }
  if(_server.hasArg("d_li")) {
    _config.set_led_color_intensity(clamp<uint8_t>(_server.arg("d_li").toInt(), 5, 100), false);
  }
  if(_server.hasArg("d_lc")) {
    _config.set_led_color_blind(strcmp(_server.arg("d_lc").c_str(), "1") == 0, false);
  }
  if(_server.hasArg("l_uh")) {
    _config.set_use_home_location(strcmp(_server.arg("l_uh").c_str(), "1") == 0, false);
  }
  if(_server.hasArg("l_ha")) {
    _config.set_home_latitude(clamp<double>(_server.arg("l_ha").toDouble(), -90.0, 90.0), false);
  }
  if(_server.hasArg("l_ho")) {
    _config.set_home_longitude(clamp<double>(_server.arg("l_ho").toDouble(), -180.0, 180.0), false);
  }

  _server.sendHeader("Location", _server.arg("next") + "?success=true");
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
        Update.abort();
      }
      break;
    }
    case UPLOAD_FILE_END: {
      if(upload.totalSize > 0 && Update.end(true)) { //true to set the size to the current progress
        DEBUG_PRINTF("\nUpdate Success: %u\n", upload.totalSize);
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


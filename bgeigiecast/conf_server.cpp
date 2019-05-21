#include <Update.h>
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

void ConfigWebServer::set_endpoints() {
  // Root
  _server.on("/", HTTP_GET, [this]() {
    handle_root();
  });

  // Save
  _server.on("/save", HTTP_GET, [this]() {
    handle_save();
  });

  // Upload get
  _server.on("/update", HTTP_GET, [this]() {
    handle_update_retrieve();
  });

  // Upload post
  _server.on("/update", HTTP_POST, [this]() {
    handle_update_complete();
  }, [this]() {
    handle_update_uploading();
  });

  // Other things
  _server.on("/favicon.ico", HTTP_GET, [this]() {
    _server.send_P(200, "image/x-icon", favicon, sizeof(favicon));
  });
  _server.on("/form.css", HTTP_GET, [this]() {
    _server.send(200, "text/css", form_style);
  });

}
void ConfigWebServer::handle_root() {
  sprintf(
      transmission_buffer,
      config_response_format,
      _server.hasArg("success") ? "<em>Configurations saved!</em> - <a href=\"/\">OK</a><br>" : "",
      _config.get_device_id(),
      _config.get_ap_password(),
      _config.get_wifi_ssid(),
      _config.get_wifi_password(),
      _config.get_api_key(),
      _config.get_use_dev() ? "checked" : "",
      _config.get_use_dev() ? "" : "checked",
      _config.get_dev_sped_up() ? "" : "checked",
      _config.get_dev_sped_up() ? "checked" : "",
      _config.get_led_color_intensity(),
      _config.is_led_color_blind() ? "" : "checked",
      _config.is_led_color_blind() ? "checked" : "",
      _config.get_use_home_location() ? "" : "checked",
      _config.get_use_home_location() ? "checked" : "",
      _config.get_home_latitude(),
      _config.get_home_longtitude(),
      _config.get_last_latitude(),
      _config.get_last_longtitude()
  );

  _server.sendHeader("Connection", "close");
  _server.send(200, "text/html", transmission_buffer);
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
    _config.set_use_dev(_server.arg("devsrv") =="1", false);
  }
  if(_server.hasArg("devfreq")) {
    _config.set_dev_sped_up(_server.arg("devfreq") =="1", false);
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

  _server.sendHeader("Location", "/?success=true");
  _server.send(302, "text/html");
}

void ConfigWebServer::handle_update_uploading() {
  DEBUG_PRINTLN("GOT IN THE handle_update_uploading");
  HTTPUpload& upload = _server.upload();
  if(upload.status == UPLOAD_FILE_START) {
    DEBUG_PRINTF("Update: %s\n", upload.filename.c_str());
    if(!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
      Update.printError(Serial);
    }
  } else if(upload.status == UPLOAD_FILE_WRITE) {
    /* flashing firmware to ESP*/
    if(Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if(upload.status == UPLOAD_FILE_END) {
    if(Update.end(true)) { //true to set the size to the current progress
      DEBUG_PRINTF("Update Success: %u\nRebooting...\n", upload.totalSize);
    } else {
      DEBUG_PRINTF("Update Failed...");
    }
  }
}

void ConfigWebServer::handle_update_complete() {
  DEBUG_PRINTLN("GOT IN THE handle_update_complete");
  _server.sendHeader("Connection", "close");
  _server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
  ESP.restart();
}

void ConfigWebServer::handle_update_retrieve() {
  DEBUG_PRINTLN("GOT IN THE handle_update_retrieve");
  _server.sendHeader("Connection", "close");
  _server.send(200, "text/html", upload_page);
}

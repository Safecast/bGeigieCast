#include <WebServer.h>
#include "http_pages.h"

const char* success_message = "<p><em>Configurations saved!</em> - <a href=\"/\">Home</a></p>";

const char* html_page_start =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<link rel='icon' href='data:image/x-icon;base64,AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAA"
    "AAgAAAAAAAAAAAAAAAEAAAAAAAAACAhYcA////AA0PEAC+pm4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAIiIiIiIiIiIiIiIiIiIiIiIiMyISESIiIiIzIhIRIiIiIiIiEhEiIiIiIiISESIiIiIiIRIRIiIiIiIRIhEiIiIiERIi"
    "ESIiIiIQIhESIiIiIiIRESIiIiIiEREiIiIiIiIRIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' type='image/x-png' />"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
    "<style>"
    "body{font-family: Helvetica;text-align: center;}"
    "#update #file-input,"
    "#update input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
    "#update input{background:#f1f1f1;border:0;padding:0 15px}"
    "#update #file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
    "#update #bar,"
    "#update #prgbar{background-color:#f1f1f1;border-radius:4px}"
    "#update #bar{background-color:lightgrey;width:0%;height:10px}"
    "#update form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
    "#update .btn{background:#3498db;color:#fff;cursor:pointer}"
    "#config{max-width:396px;margin:auto;}"
    "#config form{background-color: lightgrey;text-align: left;margin: 20px;padding: 20px;max-width: 316p;}"
    "#config input[type='text'],"
    "#config input[type='number']{max-width: 300px;width: 95%;padding: 3px;border-radius: 8px;margin-bottom: 5px;}"
    "</style>"
    "</head>"
    "<body>";

const char* html_page_end =
    "</body>"
    "</html>";

const char* HttpPages::get_home_page(uint32_t device_id) {
  sprintf(
      transmission_buffer,
      "%s" // html page start
      "<div id='config'>"
      "bGeigieCast %d<br>"
      "<ul>"
      "<li><a href='/device'>Device settings</a></li>"
      "<li><a href='/location'>Location settings</a></li>"
      "<li><a href='/connection'>Connection settings</a></li>"
      "<li><a href='/update'>Update firmware</a></li>"
      "</ul>"
      "</div>"
      "%s",  // html page end,
      html_page_start,
      device_id,
      html_page_end
  );
  return transmission_buffer;
}

const char* HttpPages::get_upload_page() {
  sprintf(
      transmission_buffer,
      "%s"
      "<div id='update'>"
      "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
      "<p id='status'>Update the firmware</p>"
      "<div id='form-content'>"
      "<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
      "<label id='file-input' for='file'>Choose file...</label>"
      "<input type='submit' class=btn value='Update'>"
      "</div>"
      "<br><br>"
      "<div id='prg'></div>"
      "<div id='prgbar'><div id='bar'></div></div>"
      "</form>"
      "<script>"
      "function sub(obj){"
      "var fileName = obj.value.split('\\\\');"
      "document.getElementById('file-input').innerHTML = fileName[fileName.length-1];"
      "};"
      "$('form').submit(function(e){"
      "e.preventDefault();"
      "$('#form-content').hide();"
      "var form = $('#upload_form')[0];"
      "var data = new FormData(form);"
      "$.ajax({"
      "url: '/update',"
      "type: 'POST',"
      "data: data,"
      "contentType: false,"
      "processData:false,"
      "xhr: function() {"
      "var xhr = new window.XMLHttpRequest();"
      "xhr.upload.addEventListener('progress', function(evt) {"
      "if (evt.lengthComputable) {"
      "$('#status').html('Uploading... This takes up to 10 minutes');"
      "var per = evt.loaded / evt.total;"
      "$('#prg').html('progress: ' + Math.round(per*100) + '%%');"
      "$('#bar').css('width',Math.round(per*100) + '%%');"
      "}"
      "}, false);"
      "return xhr;"
      "},"
      "success:function(d, s) {"
      "$('#status').html('Upload success! Restarting device...');"
      "console.log('success!') "
      "},"
      "error: function (a, b, c) {"
      "$('#status').html('Upload failed...')"
      "}"
      "});"
      "});"
      "</script>"
      "</div>"
      "%s", // html page end
      html_page_start,
      html_page_end
  );
  return transmission_buffer;
}

const char* HttpPages::get_config_device_page(
    bool display_success,
    uint32_t device_id,
    uint8_t led_intensity,
    bool colorblind
) {
  sprintf(
      transmission_buffer,
      "%s" // html page start
      "<div id='config'>"
      "<span>%s</span>"
      "<strong>Configure device</strong><br>"
      "bGeigieCast %d<br>"
      "<form action='/save?next=/device' method='POST'>"
      "LED intensity:<br><input type='number' min='5' max='100' name='led_intensity' value='%d'><br>"
      "LED Colors:<br>"
      "<input type='radio' name='led_color' value='0' %s>Default<br>"
      "<input type='radio' name='led_color' value='1' %s>Color blind<br>"
      "<input type='submit' value='Submit' style='background-color: #FF9800; font-size: initial;color: white;'>"
      "</form><br><br>"
      "</div>"
      "%s", // html page end
      html_page_start,
      display_success ? success_message : "",
      device_id,
      led_intensity,
      colorblind ? "" : "checked",
      colorblind ? "checked" : "",
      html_page_end
  );
  return transmission_buffer;
}

const char* HttpPages::get_config_network_page(
    bool display_success,
    uint32_t device_id,
    const char* device_password,
    const char* wifi_ssid,
    const char* wifi_password,
    const char* api_key,
    bool use_dev,
    bool sped_up
) {
  sprintf(
      transmission_buffer,
      "%s" // html page start
      "<div id='config'>"
      "<span>%s</span>"
      "<strong>Configure network</strong><br>"
      "bGeigieCast %d<br>"
      "<form action='/save?next=/connection' method='POST' > "
      "bGeigieCast password:<br><input type='text' name='ap_password' value='%s'><br>"
      "Network wifi ssid:<br><input type='text' name='wf_ssid' value='%s'><br>"
      "Network wifi password:<br><input type='text' name='wf_password' value='%s'><br>"
      "Safecast API key:<br><input type='text' name='apikey' value='%s'><br>"
      "Use safecast server:<br>"
      "<input type='radio' name='devsrv' value='1' %s>Development<br>"
      "<input type='radio' name='devsrv' value='0' %s>Production<br>"
      "Send frequency (dev only):<br>"
      "<input type='radio' name='devfreq' value='0' %s>5 minutes<br>"
      "<input type='radio' name='devfreq' value='1' %s>30 seconds<br>"
      "<input type='submit' value='Submit' style='background-color: #FF9800; font-size: initial;color: white;'>"
      "</form><br><br>"
      "</div>"
      "%s", // html page end
      html_page_start,
      display_success ? success_message : "",
      device_id,
      device_password,
      wifi_ssid,
      wifi_password,
      api_key,
      use_dev ? "checked" : "",
      use_dev ? "" : "checked",
      sped_up ? "" : "checked",
      sped_up ? "checked" : "",
      html_page_end
  );
  return transmission_buffer;
}

const char* HttpPages::get_config_location_page(
    bool display_success,
    uint32_t device_id,
    bool use_home_location,
    double home_latitude,
    double home_longtitude,
    double last_latitude,
    double last_longtitude
) {
  sprintf(
      transmission_buffer,
      "%s" // html page start
      "<div id='config'>"
      "<span>%s</span>"
      "<strong>Configure location</strong><br>"
      "bGeigieCast %d<br>"
      "<form action='/save?next=/location' method='POST' > "
      "Fixed mode GPS settings:<br>"
      "<input type='radio' name='use_home_loc' value='0' %s>Use GPS<br>"
      "<input type='radio' name='use_home_loc' value='1' %s>Use home location<br>"
      "Home latitude:<br><input type='number' min='-90.0000' max='90.0000' name='home_lat' id='home_lat' value='%.5f' step='0.00001'><br>"
      "Home longitude:<br><input type='number' min='-180.0000' max='180.0000' name='home_long' id='home_long' value='%.5f' step='0.00001'><br>"
      "Last known location: (<a href='#' onclick=\""
      "document.getElementById('home_lat').value = document.getElementById('last_lat').innerHTML;"
      "document.getElementById('home_long').value = document.getElementById('last_long').innerHTML;"
      "return false;"
      "\">Use this</a>)<br>"
      "Latitude: <span id='last_lat'>%.5f</span><br>"
      "Longitude: <span id='last_long'>%.5f</span><br>"
      "<input type='submit' value='Submit' style='background-color: #FF9800; font-size: initial;color: white;'>"
      "</form><br><br>"
      "</div>"
      "%s", // html page end
      html_page_start,
      display_success ? success_message : "",
      device_id,
      use_home_location ? "" : "checked",
      use_home_location ? "checked" : "",
      home_latitude,
      home_longtitude,
      last_latitude,
      last_longtitude,
      html_page_end
  );
  return transmission_buffer;
}

char HttpPages::transmission_buffer[] = "";



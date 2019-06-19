#include <unity.h>
#include <http_pages.h>
#include <conf_server.h>
#include "../test_config.h"
#include <HTTPClient.h>

// Run server
void run_server(void* server_arg) {
  ConfigWebServer* server = (ConfigWebServer*) server_arg;
  while(server->running()) {
    server->handle_requests();
    delay(10);
  }
  vTaskDelete(NULL);
}

void test_http_get_home() {
  TestEspConfig config;
  config.set_all();

  ConfigWebServer server(config);
  TEST_ASSERT_TRUE(server.connect(false));
  server.start_server();
  TaskHandle_t xHandle = NULL;
  xTaskCreate(run_server, "WebServer", 50000, &server, 1, &xHandle);
  configASSERT(xHandle);

  HTTPClient client;

  TEST_ASSERT_TRUE(client.begin("http://127.0.0.1/"))
  TEST_ASSERT_EQUAL(200, client.GET());

  server.stop();
  delay(100);
}

void test_http_post_device_config() {
  TestEspConfig config;
  config.set_all();
  ConfigWebServer server(config);
  HTTPClient client;
  char buffer[500];

  // New values to set
  const char* new_ap_password = "newappassword";
  uint8_t new_led_color_intensity = 50;
  bool new_led_color_blind = !D_LED_COLOR_BLIND;

  // Start server
  TEST_ASSERT_TRUE(server.connect(false));
  server.start_server();
  TaskHandle_t xHandle = nullptr;
  xTaskCreate(run_server, "WebServer", 50000, &server, 1, &xHandle);
  configASSERT(xHandle);

  // Check config defaults
  TEST_ASSERT_EQUAL_STRING(D_ACCESS_POINT_PASSWORD, config.get_ap_password());
  TEST_ASSERT_EQUAL(D_LED_COLOR_BLIND, config.is_led_color_blind());
  TEST_ASSERT_EQUAL(D_LED_COLOR_INTENSITY, config.get_led_color_intensity());

  // Set post data
  sprintf(
      buffer,
      "%s=%s&"
      "%s=%d&"
      "%s=%d",
      FORM_NAME_AP_LOGIN, new_ap_password,
      FORM_NAME_LED_INTENSITY, new_led_color_intensity,
      FORM_NAME_LED_COLOR, new_led_color_blind
  );

  // Post device settings
  TEST_ASSERT_TRUE(client.begin("http://127.0.0.1/save"));
  client.addHeader("Content-Type", "application/x-www-form-urlencoded");
  TEST_ASSERT_EQUAL(302, client.POST(reinterpret_cast<uint8_t*>(buffer), strlen(buffer)));

  // Check new settings
  TEST_ASSERT_EQUAL_STRING(new_ap_password, config.get_ap_password());
  TEST_ASSERT_EQUAL(new_led_color_intensity, config.get_led_color_intensity());
  TEST_ASSERT_EQUAL(new_led_color_blind, config.is_led_color_blind());

  server.stop();
}

void test_http_post_connection_config() {
  TestEspConfig config;
  config.set_all();
  ConfigWebServer server(config);
  HTTPClient client;
  char buffer[500];

  // New values to set
  const char* new_wifi_ssid = "mynewssid";
  const char* new_wifi_password = "mynewpassword";
  const char* new_api_key = "mynewapikey";
  bool new_use_dev = !D_USE_DEV_SERVER;
  bool new_dev_sped_up = true;

  // Start server
  TEST_ASSERT_TRUE(server.connect(false));
  server.start_server();
  TaskHandle_t xHandle = nullptr;
  xTaskCreate(run_server, "WebServer", 50000, &server, 1, &xHandle);
  configASSERT(xHandle);

  // Check config defaults
  TEST_ASSERT_EQUAL_STRING(D_WIFI_SSID, config.get_wifi_ssid());
  TEST_ASSERT_EQUAL_STRING(D_WIFI_PASSWORD, config.get_wifi_password());
  TEST_ASSERT_EQUAL_STRING(D_APIKEY, config.get_api_key());
  TEST_ASSERT_EQUAL(D_USE_DEV_SERVER, config.get_use_dev());
  TEST_ASSERT_EQUAL(false, config.get_dev_sped_up());

  // Set post data
  sprintf(
      buffer,
      "%s=%s&"
      "%s=%s&"
      "%s=%s&"
      "%s=%d&"
      "%s=%d",
      FORM_NAME_WIFI_SSID, new_wifi_ssid,
      FORM_NAME_WIFI_PASS, new_wifi_password,
      FORM_NAME_API_KEY, new_api_key,
      FORM_NAME_USE_DEV, new_use_dev,
      FORM_NAME_DEV_FREQ, new_dev_sped_up
  );

  // Post connection settings
  TEST_ASSERT_TRUE(client.begin("http://127.0.0.1/save"));
  client.addHeader("Content-Type", "application/x-www-form-urlencoded");
  TEST_ASSERT_EQUAL(302, client.POST(reinterpret_cast<uint8_t*>(buffer), strlen(buffer)));

  // Check new settings
  TEST_ASSERT_EQUAL_STRING(new_wifi_ssid, config.get_wifi_ssid());
  TEST_ASSERT_EQUAL_STRING(new_wifi_password, config.get_wifi_password());
  TEST_ASSERT_EQUAL_STRING(new_api_key, config.get_api_key());
  TEST_ASSERT_EQUAL(new_use_dev, config.get_use_dev());
  TEST_ASSERT_EQUAL(new_dev_sped_up, config.get_dev_sped_up());

  server.stop();
}

void test_http_post_location_config() {
  TestEspConfig config;
  config.set_all();
  ConfigWebServer server(config);
  HTTPClient client;
  char buffer[500];

  // New values to set
  bool new_use_home_location = true;
  double new_home_longitude = 32.24;
  double new_home_latitude = 31.23;

  // Start server
  TEST_ASSERT_TRUE(server.connect(false));
  server.start_server();
  TaskHandle_t xHandle = nullptr;
  xTaskCreate(run_server, "WebServer", 50000, &server, 1, &xHandle);
  configASSERT(xHandle);

  // Check config defaults
  TEST_ASSERT_EQUAL(false, config.get_use_home_location());
  TEST_ASSERT_EQUAL_FLOAT(0.0, config.get_home_longitude());
  TEST_ASSERT_EQUAL_FLOAT(0.0, config.get_home_latitude());

  // Set post data
  sprintf(
      buffer,
      "%s=%d&"
      "%s=%f&"
      "%s=%f",
      FORM_NAME_LOC_HOME, new_use_home_location,
      FORM_NAME_LOC_HOME_LAT, new_home_latitude,
      FORM_NAME_LOC_HOME_LON, new_home_longitude
  );

  // Post location settings
  TEST_ASSERT_TRUE(client.begin("http://127.0.0.1/save"));
  client.addHeader("Content-Type", "application/x-www-form-urlencoded");
  TEST_ASSERT_EQUAL(302, client.POST(reinterpret_cast<uint8_t*>(buffer), strlen(buffer)));

  // Check new settings
  TEST_ASSERT_EQUAL(new_use_home_location, config.get_use_home_location());
  TEST_ASSERT_EQUAL_FLOAT(new_home_longitude, config.get_home_longitude());
  TEST_ASSERT_EQUAL_FLOAT(new_home_latitude, config.get_home_latitude());

  server.stop();
}

#include <Arduino.h>
#include <unity.h>

void test_render_home_page();
void test_render_update_page();
void test_render_config_device_page();
void test_render_config_connection_page();
void test_render_config_location_page();
void test_pure_css();
void test_favicon();

void test_http_get_home();
void test_http_post_device_config();
void test_http_post_connection_config();
void test_http_post_location_config();

void setup() {
  delay(2000);
  // Unit test start
  UNITY_BEGIN();

  RUN_TEST(test_render_home_page);
  RUN_TEST(test_render_update_page);
  RUN_TEST(test_render_config_device_page);
  RUN_TEST(test_render_config_connection_page);
  RUN_TEST(test_render_config_location_page);
  RUN_TEST(test_pure_css);
  RUN_TEST(test_favicon);

  RUN_TEST(test_http_get_home);
  RUN_TEST(test_http_post_device_config);
  RUN_TEST(test_http_post_connection_config);
  RUN_TEST(test_http_post_location_config);

  // Unit test done
  UNITY_END();
}

void loop() {
}

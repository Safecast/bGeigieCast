#include <Arduino.h>
#include <unity.h>

void test_get_home_page();
void test_get_update_page();
void test_get_config_device_page();
void test_get_config_connection_page();
void test_get_config_location_page();
void test_pure_css();
void test_favicon();

void setup() {
  delay(2000);
  // Unit test start
  UNITY_BEGIN();

  RUN_TEST(test_get_home_page);
  RUN_TEST(test_get_update_page);
  RUN_TEST(test_get_config_device_page);
  RUN_TEST(test_get_config_connection_page);
  RUN_TEST(test_get_config_location_page);
  RUN_TEST(test_pure_css);
  RUN_TEST(test_favicon);

  // Unit test done
  UNITY_END();
}

void loop() {
}

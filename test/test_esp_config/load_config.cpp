#include <unity.h>

#include "../test_config.h"

/**
 * Test setting all config from memory
 */
void test_initial_config(void) {
  TestEspConfig config;

  config.set_all();

  TEST_ASSERT_EQUAL_STRING(D_ACCESS_POINT_PASSWORD, config.get_ap_password());
  TEST_ASSERT_EQUAL_STRING(D_WIFI_SSID, config.get_wifi_ssid());
  TEST_ASSERT_EQUAL_STRING(D_WIFI_PASSWORD, config.get_wifi_password());
  TEST_ASSERT_EQUAL_STRING(D_APIKEY, config.get_api_key());
  TEST_ASSERT_EQUAL(D_USE_DEV_SERVER, config.get_use_dev());
  TEST_ASSERT_EQUAL(false, config.get_dev_sped_up());
  TEST_ASSERT_EQUAL(D_LED_COLOR_BLIND, config.is_led_color_blind());
  TEST_ASSERT_EQUAL(D_LED_COLOR_INTENSITY, config.get_led_color_intensity());
  TEST_ASSERT_EQUAL(false, config.get_use_home_location());
  TEST_ASSERT_EQUAL_FLOAT(0.0, config.get_home_longitude());
  TEST_ASSERT_EQUAL_FLOAT(0.0, config.get_home_latitude());
  TEST_ASSERT_EQUAL_FLOAT(0.0, config.get_last_longitude());
  TEST_ASSERT_EQUAL_FLOAT(0.0, config.get_last_latitude());

}

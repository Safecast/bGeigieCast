#include <unity.h>

#include "../test_config.h"

/**
 * Test resetting all config from memory
 */
void test_reset_config(void) {
  TestEspConfig config;

  config.set_ap_password("NEW VALUE", false);
  config.set_wifi_ssid("NEW VALUE!", false);
  config.set_wifi_password("NEW VALUE!", false);
  config.set_api_key("NEW VALUE!", false);
  config.set_use_dev(false, false);
  config.set_dev_sped_up(true, false);
  config.set_led_color_blind(!D_LED_COLOR_BLIND, false);
  config.set_led_color_intensity(33, false);
  config.set_use_home_location(true, false);
  config.set_home_longitude(4.42, false);
  config.set_home_latitude(11.04, false);
  config.set_last_longitude(42.3, false);
  config.set_last_latitude(412.41, false);


  TEST_ASSERT_NOT_EQUAL(0, strcmp(D_ACCESS_POINT_PASSWORD, config.get_ap_password()));
  TEST_ASSERT_NOT_EQUAL(0, strcmp(D_WIFI_SSID, config.get_wifi_ssid()));
  TEST_ASSERT_NOT_EQUAL(0, strcmp(D_WIFI_PASSWORD, config.get_wifi_password()));
  TEST_ASSERT_NOT_EQUAL(0, strcmp(D_APIKEY, config.get_api_key()));
  TEST_ASSERT_NOT_EQUAL(D_USE_DEV_SERVER, config.get_use_dev());
  TEST_ASSERT_NOT_EQUAL(false, config.get_dev_sped_up());
  TEST_ASSERT_NOT_EQUAL(D_LED_COLOR_BLIND, config.is_led_color_blind());
  TEST_ASSERT_NOT_EQUAL(D_LED_COLOR_INTENSITY, config.get_led_color_intensity());
  TEST_ASSERT_NOT_EQUAL(false, config.get_use_home_location());
  TEST_ASSERT_NOT_EQUAL(0.0, config.get_home_longitude());
  TEST_ASSERT_NOT_EQUAL(0.0, config.get_home_latitude());
  TEST_ASSERT_NOT_EQUAL(0.0, config.get_last_longitude());
  TEST_ASSERT_NOT_EQUAL(0.0, config.get_last_latitude());


  config.reset_defaults();

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

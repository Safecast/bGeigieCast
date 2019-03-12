#include <unity.h>

#include <user_config.h>
#include <esp_config.h>

/**
 * Test resetting all config from memory
 */
void test_reset_config(void) {
  EspConfig config;

  config.reset_defaults();

  TEST_ASSERT_EQUAL_STRING(config.get_ap_ssid(), D_ACCESS_POINT_SSID);
  TEST_ASSERT_EQUAL_STRING(config.get_ap_password(), D_ACCESS_POINT_PASSWORD);
  TEST_ASSERT_EQUAL_STRING(config.get_wifi_ssid(), D_WIFI_SSID);
  TEST_ASSERT_EQUAL_STRING(config.get_wifi_password(), D_WIFI_PASSWORD);
  TEST_ASSERT_EQUAL_STRING(config.get_api_key(), D_APIKEY);
  TEST_ASSERT_EQUAL(config.get_use_dev(), D_USE_DEV_SERVER);
}

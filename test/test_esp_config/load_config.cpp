#include <unity.h>

#include "../test_config.h"

/**
 * Test setting all config from memory
 */
void test_initial_config(void) {
  TestEspConfig config;

  config.set_all();

  TEST_ASSERT_EQUAL_STRING(D_ACCESS_POINT_SSID, config.get_ap_ssid());
  TEST_ASSERT_EQUAL_STRING(D_ACCESS_POINT_PASSWORD, config.get_ap_password());
  TEST_ASSERT_EQUAL_STRING(D_WIFI_SSID, config.get_wifi_ssid());
  TEST_ASSERT_EQUAL_STRING(D_WIFI_PASSWORD, config.get_wifi_password());
  TEST_ASSERT_EQUAL_STRING(D_APIKEY, config.get_api_key());
  TEST_ASSERT_EQUAL(D_USE_DEV_SERVER, config.get_use_dev());
  TEST_ASSERT_EQUAL(D_INIT_STATIONARY, config.is_init_stationary());
}

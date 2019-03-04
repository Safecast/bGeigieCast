#include <unity.h>

#include <user_config.h>
#include <esp_config.h>

/**
 * Test resetting all config from memory
 */
void test_reset_config(void) {
  EspConfig config;

  config.reset_defaults();

  char val_buff[CONFIG_VAL_MAX];
  config.get_ap_ssid(val_buff);
  TEST_ASSERT_EQUAL_STRING(val_buff, D_ACCESS_POINT_SSID);
  config.get_ap_password(val_buff);
  TEST_ASSERT_EQUAL_STRING(val_buff, D_ACCESS_POINT_PASSWORD);
  config.get_wifi_ssid(val_buff);
  TEST_ASSERT_EQUAL_STRING(val_buff, D_WIFI_SSID);
  config.get_wifi_password(val_buff);
  TEST_ASSERT_EQUAL_STRING(val_buff, D_WIFI_PASSWORD);
  config.get_api_key(val_buff);
  TEST_ASSERT_EQUAL_STRING(val_buff, D_APIKEY);
  TEST_ASSERT_EQUAL(config.get_use_dev(), D_USE_DEV_SERVER);
}

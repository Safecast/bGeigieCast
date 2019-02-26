#include <unity.h>

#include <user_config.h>
#include <esp_config.h>

/**
 * Test setting new values to memory
 */
void test_set_config(void) {
  EspConfig config;

  config.set_all();

  const char* new_string_val = "some new string value";
  const char* long_string_val = "some new string value which is way too long for the config to save!!";

  TEST_ASSERT_GREATER_THAN(CONFIG_VAL_MAX, long_string_val);

  char val_buff[CONFIG_VAL_MAX];

  // Set new ap ssid
  config.set_ap_ssid(new_string_val);
  config.get_ap_ssid(val_buff);
  TEST_ASSERT_EQUAL_STRING(val_buff, new_string_val);

  // Set ap ssid with invalid value
  config.set_ap_ssid(long_string_val);
  config.get_ap_ssid(val_buff);
  TEST_ASSERT_NOT_EQUAL(strcmp(val_buff, long_string_val), 0);

  // Should still return the old, correct value
  TEST_ASSERT_EQUAL_STRING(val_buff, new_string_val);
}

#include <Arduino.h>
#include <unity.h>

#include <esp_config.h>


// To restore saved configs after test
EspConfig saved_config;

void save_current_config(void) {
  saved_config.set_all();
}

void restore_current_config(void) {
  char temp_buffer[CONFIG_VAL_MAX];
  saved_config.get_wifi_password(temp_buffer);
  saved_config.set_wifi_password(temp_buffer);
  saved_config.get_ap_password(temp_buffer);
  saved_config.set_ap_password(temp_buffer);
  saved_config.get_ap_ssid(temp_buffer);
  saved_config.set_ap_ssid(temp_buffer);
  saved_config.get_api_key(temp_buffer);
  saved_config.set_api_key(temp_buffer);
  saved_config.get_wifi_ssid(temp_buffer);
  saved_config.set_wifi_ssid(temp_buffer);
  saved_config.set_use_dev(saved_config.get_use_dev());
}

void test_initial_config(void);
void test_reset_config(void);
void test_set_config(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  save_current_config();

  RUN_TEST(test_reset_config);

  RUN_TEST(test_initial_config);

  RUN_TEST(test_set_config);

  restore_current_config();

  UNITY_END();
}

void loop() {
}
#include <Arduino.h>
#include <unity.h>

#include <esp_config.h>


// To restore saved configs after test
EspConfig saved_config;

void save_current_config(void) {
  saved_config.set_all();
}

void restore_current_config(void) {
  saved_config.set_wifi_password(saved_config.get_wifi_password());
  saved_config.set_ap_password(saved_config.get_ap_password());
  saved_config.set_ap_ssid(saved_config.get_ap_ssid());
  saved_config.set_api_key(saved_config.get_api_key());
  saved_config.set_wifi_ssid(saved_config.get_wifi_ssid());
  saved_config.set_use_dev(saved_config.get_use_dev());
}

void test_initial_config(void);
void test_reset_config(void);
void test_set_config(void);

void setup() {
  delay(2000);
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_INPUT;
  io_conf.pin_bit_mask = 1ULL << 22;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  gpio_config(&io_conf);

  gpio_set_intr_type((gpio_num_t) 22, GPIO_INTR_ANYEDGE);
  gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);

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

#include <Arduino.h>
#include <unity.h>

void test_int_buffer();
void test_dm_to_dd();
void test_button_status_pullup();
void test_button_status_pulldown();
void test_button_with_callback_functions();
void test_button_with_observer();
void test_button_debounce();

void setup() {
  delay(2000);

  gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);

  // Unit test start
  UNITY_BEGIN();

  RUN_TEST(test_int_buffer);
  RUN_TEST(test_dm_to_dd);
  RUN_TEST(test_button_status_pullup);
  RUN_TEST(test_button_status_pulldown);
  RUN_TEST(test_button_with_callback_functions);
  RUN_TEST(test_button_with_observer);
  RUN_TEST(test_button_debounce);

  // Unit test done
  UNITY_END();
}

void loop() {
}

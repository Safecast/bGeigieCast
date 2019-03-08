#include <Arduino.h>
#include <unity.h>

void test_led_builtin_pin_number(void);
void test_led_builtin_state_high(void);
void test_led_builtin_state_low(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_led_builtin_pin_number);
  RUN_TEST(test_led_builtin_state_high);
  RUN_TEST(test_led_builtin_state_low);

  UNITY_END();
}

void loop() {
}

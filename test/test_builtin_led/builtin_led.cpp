#include <Arduino.h>
#include <unity.h>

/**
 * Check if builtin led is correct
 * - Example test from: https://docs.platformio.org/en/latest/tutorials/core/unit_testing_blink.html
 */
void test_led_builtin_pin_number(void) {
  TEST_ASSERT_EQUAL(2, LED_BUILTIN);
}

/**
 * Check if write HIGH works (led on)
 * - Example test from: https://docs.platformio.org/en/latest/tutorials/core/unit_testing_blink.html
 */
void test_led_builtin_state_high(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

/**
 * Check if write LOW works (led off)
 * - Example test from: https://docs.platformio.org/en/latest/tutorials/core/unit_testing_blink.html
 */
void test_led_builtin_state_low(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));
}

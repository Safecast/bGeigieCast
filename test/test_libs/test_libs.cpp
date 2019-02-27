#include <Arduino.h>
#include <unity.h>

void test_int_buffer();
void test_button();

void setup() {
  delay(2000);
  // Unit test start
  UNITY_BEGIN();

  RUN_TEST(test_int_buffer);

  RUN_TEST(test_button);

  // Unit test done
  UNITY_END();
}

void loop() {
}

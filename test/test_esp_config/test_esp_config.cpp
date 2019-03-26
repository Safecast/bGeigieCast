#include <Arduino.h>
#include <unity.h>

void test_initial_config(void);
void test_reset_config(void);
void test_set_config(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(test_reset_config);

  RUN_TEST(test_initial_config);

  RUN_TEST(test_set_config);

  UNITY_END();
}

void loop() {
}

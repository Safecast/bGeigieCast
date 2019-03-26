#include <Arduino.h>
#include <unity.h>

void test_readings_saving(void);

void setup() {
  delay(2000);
  // Unit test start
  UNITY_BEGIN();

  RUN_TEST(test_readings_saving);
  // Unit test done
  UNITY_END();
}

void loop() {
}

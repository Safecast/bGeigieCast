#include <Arduino.h>
#include <unity.h>

void controller_init(void);
void controller_state_transitions(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(controller_init);

  RUN_TEST(controller_state_transitions);

  UNITY_END();
}

void loop() {
}

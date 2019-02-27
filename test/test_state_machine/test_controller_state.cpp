#include <Arduino.h>
#include <unity.h>

void controller_init(void);
void controller_ap_server(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(controller_init);

  RUN_TEST(controller_ap_server);

  UNITY_END();
}

void loop() {
}

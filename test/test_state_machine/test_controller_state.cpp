#include <Arduino.h>
#include <unity.h>

void controller_init(void);
void controller_state_transitions_init_mobile(void);
void controller_state_transitions_init_server(void);
void controller_state_transitions_mobile_stationary(void);
void controller_state_transitions_connecting_test_connected(void);
void controller_state_transitions_connecting_error_connected(void);
void controller_state_transitions_connected_error(void);
void controller_state_transitions_connected_reconnect(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(controller_init);

  RUN_TEST(controller_state_transitions_init_mobile);
  RUN_TEST(controller_state_transitions_init_server);
  RUN_TEST(controller_state_transitions_mobile_stationary);
  RUN_TEST(controller_state_transitions_connecting_test_connected);
  RUN_TEST(controller_state_transitions_connecting_error_connected);
  RUN_TEST(controller_state_transitions_connected_error);
  RUN_TEST(controller_state_transitions_connected_reconnect);

  UNITY_END();
}

void loop() {
}

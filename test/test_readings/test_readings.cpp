#include <Arduino.h>
#include <unity.h>

void reading_parsing(void);
void reading_parsing_inverse_lat_long(void);
void reading_parsing_invalid_format(void);
void reading_parsing_invalid_sensor(void);
void reading_parsing_invalid_gps(void);

void reading_parsing_stationary(void);
void reading_parsing_mobile(void);
void reading_parsing_invalid(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(reading_parsing);
  RUN_TEST(reading_parsing_inverse_lat_long);
  RUN_TEST(reading_parsing_invalid_format);
  RUN_TEST(reading_parsing_invalid_sensor);
  RUN_TEST(reading_parsing_invalid_gps);

  RUN_TEST(reading_parsing_stationary);
  RUN_TEST(reading_parsing_mobile);
  RUN_TEST(reading_parsing_invalid);

  UNITY_END();
}

void loop() {
}

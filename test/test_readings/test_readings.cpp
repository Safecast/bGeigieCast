#include <Arduino.h>
#include <unity.h>

void reading_parsing(void);
void reading_parsing_inverse_lat_long(void);
void reading_parsing_invalid_format(void);
void reading_parsing_invalid_sensor(void);
void reading_parsing_invalid_gps(void);

void reading_json_stationary(void);
void reading_json_mobile(void);
void reading_json_invalid(void);

void reading_merging_new(void);
void reading_merging_normal(void);
void reading_merging_multiple(void);

void test_dms_to_dd(void);

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(reading_parsing);
  RUN_TEST(reading_parsing_inverse_lat_long);
  RUN_TEST(reading_parsing_invalid_format);
  RUN_TEST(reading_parsing_invalid_sensor);
  RUN_TEST(reading_parsing_invalid_gps);

  RUN_TEST(reading_json_stationary);
  RUN_TEST(reading_json_mobile);
  RUN_TEST(reading_json_invalid);

  RUN_TEST(reading_merging_new);
  RUN_TEST(reading_merging_normal);
  RUN_TEST(reading_merging_multiple);

  RUN_TEST(test_dms_to_dd);

  UNITY_END();
}

void loop() {
}

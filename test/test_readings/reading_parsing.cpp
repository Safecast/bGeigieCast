#include <unity.h>
#include <reading.h>

/**
 * Test parsing of a valid reading
 */
void reading_parsing(void) {
  const char* valid_str = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46";

  Reading r(valid_str);

  TEST_ASSERT_EQUAL(ReadingValidity::e_unparsed, r.get_validity());
  
  r.parse_values();

  TEST_ASSERT_EQUAL(ReadingValidity::e_valid, r.get_validity());

  TEST_ASSERT_EQUAL(204, r.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r.get_cpm());
  TEST_ASSERT_EQUAL(63, r.get_cpb());
  TEST_ASSERT_EQUAL(33895, r.get_total_count());
  TEST_ASSERT_EQUAL_INT8('A', r.get_geiger_status());
  TEST_ASSERT_EQUAL_FLOAT(5641.7788, r.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(1411.8820, r.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(9861.20, r.get_altitude());
  TEST_ASSERT_EQUAL_INT8('A', r.get_gps_status());
  TEST_ASSERT_EQUAL(109, r.get_sat_count());
  TEST_ASSERT_EQUAL_STRING("9*46", r.get_precision());
}

/**
 * Test parsing of a valid reading
 */
void reading_parsing_inverse_lat_long(void) {
  const char* valid_str = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,S,1411.8820,W,9861.20,A,109,9*46";

  Reading r(valid_str);

  TEST_ASSERT_EQUAL(ReadingValidity::e_unparsed, r.get_validity());

  r.parse_values();

  TEST_ASSERT_EQUAL(ReadingValidity::e_valid, r.get_validity());

  TEST_ASSERT_EQUAL(204, r.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r.get_cpm());
  TEST_ASSERT_EQUAL(63, r.get_cpb());
  TEST_ASSERT_EQUAL(33895, r.get_total_count());
  TEST_ASSERT_EQUAL_INT8('A', r.get_geiger_status());
  TEST_ASSERT_EQUAL_FLOAT(-5641.7788, r.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(-1411.8820, r.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(9861.20, r.get_altitude());
  TEST_ASSERT_EQUAL_INT8('A', r.get_gps_status());
  TEST_ASSERT_EQUAL(109, r.get_sat_count());
  TEST_ASSERT_EQUAL_STRING("9*46", r.get_precision());
}

/**
 * Test parsing of an invalid reading
 */
void reading_parsing_invalid_format(void) {
  const char* invalid_str = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895";

  Reading r(invalid_str);

  r.parse_values();

  TEST_ASSERT_EQUAL(ReadingValidity::e_invalid_string, r.get_validity());
}

/**
 * Test parsing of a valid reading with invalid sensor
 */
void reading_parsing_invalid_sensor(void) {
  const char* invalid_sensor = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,V,5641.7788,P,1411.8820,E,9861.20,A,109,9*46";

  Reading r(invalid_sensor);

  r.parse_values();

  TEST_ASSERT_EQUAL(ReadingValidity::e_invalid_sensor, r.get_validity());
}

/**
 * Test parsing of a valid reading with invalid gps
 */
void reading_parsing_invalid_gps(void) {
  const char* invalid_gps = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,P,1411.8820,E,9861.20,V,109,9*46";

  Reading r(invalid_gps);

  r.parse_values();

  TEST_ASSERT_EQUAL(ReadingValidity::e_invalid_gps, r.get_validity());
}

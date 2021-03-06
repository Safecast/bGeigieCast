#include <unity.h>
#include <reading.h>
#include <dms_dd.h>

/**
 * Test parsing of a valid reading
 */
void reading_parsing(void) {
  const char* valid_str = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46";

  Reading r(valid_str);

  TEST_ASSERT(r.get_status() & k_reading_parsed);
  TEST_ASSERT(r.get_status() & k_reading_valid);
  TEST_ASSERT(r.get_status() & k_reading_sensor_ok);
  TEST_ASSERT(r.get_status() & k_reading_gps_ok);
  TEST_ASSERT(r.get_status() & k_reading_checksum_ok);

  TEST_ASSERT_EQUAL(2041, r.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r.get_cpm());
  TEST_ASSERT_EQUAL(63, r.get_cpb());
  TEST_ASSERT_EQUAL(33895, r.get_total_count());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(5641.7788), r.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(1411.8820), r.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(9861.2, r.get_altitude());
  TEST_ASSERT_EQUAL(109, r.get_sat_count());
  TEST_ASSERT_EQUAL_FLOAT(9, r.get_precision());

  // Test copy constructor
  Reading r2 = r;

  TEST_ASSERT_EQUAL(2041, r2.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r2.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r2.get_cpm());
  TEST_ASSERT_EQUAL(63, r2.get_cpb());
  TEST_ASSERT_EQUAL(33895, r2.get_total_count());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(5641.7788), r2.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(1411.8820), r2.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(9861.2, r2.get_altitude());
  TEST_ASSERT_EQUAL(109, r2.get_sat_count());
  TEST_ASSERT_EQUAL_FLOAT(9, r2.get_precision());
  
}

/**
 * Test parsing of a valid reading
 */
void reading_parsing_inverse_lat_long(void) {
  const char* valid_str = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,S,1411.8820,W,9861.20,A,109,9*46";

  Reading r(valid_str);

  TEST_ASSERT(r.get_status() & k_reading_parsed);
  TEST_ASSERT(r.get_status() & k_reading_valid);
  TEST_ASSERT(r.get_status() & k_reading_sensor_ok);
  TEST_ASSERT(r.get_status() & k_reading_gps_ok);
  TEST_ASSERT(r.get_status() & k_reading_checksum_ok);

  TEST_ASSERT_EQUAL(2041, r.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r.get_cpm());
  TEST_ASSERT_EQUAL(63, r.get_cpb());
  TEST_ASSERT_EQUAL(33895, r.get_total_count());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(-5641.7788), r.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(-1411.8820), r.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(9861.2, r.get_altitude());
  TEST_ASSERT_EQUAL(109, r.get_sat_count());
  TEST_ASSERT_EQUAL_FLOAT(9, r.get_precision());
}

/**
 * Test parsing of an invalid reading
 */
void reading_parsing_invalid_format(void) {
  const char* invalid_str = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895";

  Reading r(invalid_str);

  TEST_ASSERT(r.get_status() & k_reading_parsed);
  TEST_ASSERT_FALSE(r.get_status() & k_reading_valid);
  TEST_ASSERT_FALSE(r.get_status() & k_reading_sensor_ok);
  TEST_ASSERT_FALSE(r.get_status() & k_reading_gps_ok);
  TEST_ASSERT_FALSE(r.get_status() & k_reading_checksum_ok);
}

/**
 * Test parsing of a valid reading with invalid sensor
 */
void reading_parsing_invalid_sensor(void) {
  const char* invalid_sensor = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,V,5641.7788,P,1411.8820,E,9861.20,A,109,9*46";

  Reading r(invalid_sensor);

  TEST_ASSERT(r.get_status() & k_reading_parsed);
  TEST_ASSERT(r.get_status() & k_reading_valid);
  TEST_ASSERT_FALSE(r.get_status() & k_reading_sensor_ok);
  TEST_ASSERT(r.get_status() & k_reading_gps_ok);
  TEST_ASSERT(r.get_status() & k_reading_checksum_ok);
}

/**
 * Test parsing of a valid reading with invalid gps
 */
void reading_parsing_invalid_gps(void) {
  const char* invalid_gps = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,P,1411.8820,E,9861.20,V,109,9*46";

  Reading r(invalid_gps);

  TEST_ASSERT(r.get_status() & k_reading_parsed);
  TEST_ASSERT(r.get_status() & k_reading_valid);
  TEST_ASSERT(r.get_status() & k_reading_sensor_ok);
  TEST_ASSERT_FALSE(r.get_status() & k_reading_gps_ok);
  TEST_ASSERT(r.get_status() & k_reading_checksum_ok);
}

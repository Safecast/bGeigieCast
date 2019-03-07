#include <unity.h>
#include <reading.h>


/**
 * Test merging of new merging
 */
void reading_merging_new(void) {
  const char* reading_str = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46";

  Reading r; // Empty
  Reading r2(reading_str);

  r += r2;

  // Reading r should have all values of r2
  TEST_ASSERT_EQUAL(204, r.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r.get_cpm());
  TEST_ASSERT_EQUAL(63, r.get_cpb());
  TEST_ASSERT_EQUAL(33895, r.get_total_count());
  TEST_ASSERT_EQUAL_INT8('A', r.get_geiger_status());
  TEST_ASSERT_EQUAL_FLOAT(56.4177, r.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(14.1188, r.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(98.6120, r.get_altitude());
  TEST_ASSERT_EQUAL_INT8('A', r.get_gps_status());
  TEST_ASSERT_EQUAL(109, r.get_sat_count());
  TEST_ASSERT_EQUAL_FLOAT(9, r.get_precision());
  TEST_ASSERT_EQUAL(0x46, r.get_checksum());
}

/**
 * Test merging of normal merging
 */
void reading_merging_normal(void) {
  const char* reading_str1 = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1311.9100,E,9861.20,A,109,9*46";
  const char* reading_str2 = "$BNRDD,204,2012-09-20T16:54:58Z,796,83,33915,A,5441.7788,N,1411.9100,E,9821.20,A,101,5*11";

  Reading r1(reading_str1);
  Reading r2(reading_str2);

  r1 += r2;

  // Same device id
  TEST_ASSERT_EQUAL(204, r1.get_device_id());
  // Latest datetime
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:54:58Z", r1.get_iso_timestr());
  // Average cpm
  TEST_ASSERT_EQUAL(786, r1.get_cpm());
  // Average cpb
  TEST_ASSERT_EQUAL(73, r1.get_cpb());
  // latest total count
  TEST_ASSERT_EQUAL(33915, r1.get_total_count());
  // Best geiger status
  TEST_ASSERT_EQUAL_INT8('A', r1.get_geiger_status());
  // Average latitude
  TEST_ASSERT_EQUAL_FLOAT(55.4178, r1.get_latitude());
  // Average longitude
  TEST_ASSERT_EQUAL_FLOAT(13.6191, r1.get_longitude());
  // Average altitude
  TEST_ASSERT_EQUAL_FLOAT(98.4120, r1.get_altitude());
  // Best gps status
  TEST_ASSERT_EQUAL_INT8('A', r1.get_gps_status());
  // Average satellite count
  TEST_ASSERT_EQUAL(105, r1.get_sat_count());
  // Average precision
  TEST_ASSERT_EQUAL_FLOAT(7, r1.get_precision());

  // TODO: recalculate checksum if needed for API
//  TEST_ASSERT_EQUAL(..., r.get_checksum());
}

/**
 * Test merging of multiple merging
 */
void reading_merging_multiple(void) {
  const char* reading_str1 = "$BNRDD,204,2012-09-20T16:53:58Z,776,63,33895,A,5681.7188,N,1411.8420,E,9861.20,A,109,9*46";
  const char* reading_str2 = "$BNRDD,204,2012-09-20T16:54:58Z,796,83,33915,A,5611.7666,N,1399.8100,E,9761.00,A,101,5*11";
  const char* reading_str3 = "$BNRDD,204,2012-09-20T16:55:58Z,762,77,33955,A,5531.7373,N,1451.8611,E,9661.05,A,91,9*41";
  const char* reading_str4 = "$BNRDD,204,2012-09-20T16:56:58Z,780,73,33985,A,5611.7771,N,1311.8815,E,9561.08,A,85,9*19";

  Reading r1(reading_str1);
  Reading r2(reading_str2);
  Reading r3(reading_str3);
  Reading r4(reading_str4);

  r1 += r2;
  r1 += r3;
  r1 += r4;

  // Same device id
  TEST_ASSERT_EQUAL(204, r1.get_device_id());
  // Latest datetime
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:56:58Z", r1.get_iso_timestr());
  // Average cpm
  TEST_ASSERT_EQUAL(778, r1.get_cpm());
  // Average cpb
  TEST_ASSERT_EQUAL(73, r1.get_cpb());
  // latest total count
  TEST_ASSERT_EQUAL(33985, r1.get_total_count());
  // Best geiger status
  TEST_ASSERT_EQUAL_INT8('A', r1.get_geiger_status());
  // Average latitude
  TEST_ASSERT_EQUAL_FLOAT(56.0925, r1.get_latitude());
  // Average longitude
  TEST_ASSERT_EQUAL_FLOAT(13.9385, r1.get_longitude());
  // Average altitude
  TEST_ASSERT_EQUAL_FLOAT(97.1108, r1.get_altitude());
  // Best gps status
  TEST_ASSERT_EQUAL_INT8('A', r1.get_gps_status());
  // Average satellite count
  TEST_ASSERT_EQUAL(96, r1.get_sat_count());
  // Average precision
  TEST_ASSERT_EQUAL_FLOAT(8, r1.get_precision());
}

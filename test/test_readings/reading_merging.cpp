#include <unity.h>
#include <reading.h>
#include <dms_dd.h>


/**
 * Test merging of new merging
 */
void reading_merging_new(void) {
  const char* reading_str = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46";

  Reading r; // Empty
  Reading r2(reading_str);

  r += r2;

  // Reading r should have all values of r2
  TEST_ASSERT_EQUAL(2041, r.get_device_id());
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:53:58Z", r.get_iso_timestr());
  TEST_ASSERT_EQUAL(776, r.get_cpm());
  TEST_ASSERT_EQUAL(63, r.get_cpb());
  TEST_ASSERT_EQUAL(33895, r.get_total_count());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(5641.7788), r.get_latitude());
  TEST_ASSERT_EQUAL_FLOAT(dm_to_dd(1411.9100), r.get_longitude());
  TEST_ASSERT_EQUAL_FLOAT(9861.2, r.get_altitude());
  TEST_ASSERT_EQUAL(109, r.get_sat_count());
  TEST_ASSERT_EQUAL_FLOAT(9, r.get_precision());
}

/**
 * Test merging of normal merging
 */
void reading_merging_normal(void) {
  const char* reading_str1 = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1311.9100,E,9861.20,A,109,9*46";
  const char* reading_str2 = "$BNRDD,2041,2012-09-20T16:54:58Z,796,83,33915,A,5441.7788,N,1411.9100,E,9821.20,A,101,5*11";

  Reading r1(reading_str1);
  Reading r2(reading_str2);

  r1 += r2;

  // Same device id
  TEST_ASSERT_EQUAL(2041, r1.get_device_id());
  // Latest datetime
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:54:58Z", r1.get_iso_timestr());
  // Average cpm
  TEST_ASSERT_EQUAL(786, r1.get_cpm());
  // Average cpb
  TEST_ASSERT_EQUAL(73, r1.get_cpb());
  // latest total count
  TEST_ASSERT_EQUAL(33915, r1.get_total_count());
  // Average latitude
  double avg_lat = (dm_to_dd(5641.7788) + dm_to_dd(5441.7788)) / 2;
  TEST_ASSERT_EQUAL_FLOAT(avg_lat, r1.get_latitude());
  // Average longitude
  double avg_long = (dm_to_dd(1411.9100) + dm_to_dd(1311.9100)) / 2;
  TEST_ASSERT_EQUAL_FLOAT(avg_long, r1.get_longitude());
  // Average altitude
  double avg_alt = (9861.20 + 9821.20) / 2;
  TEST_ASSERT_EQUAL_FLOAT(avg_alt, r1.get_altitude());
  // Average satellite count
  TEST_ASSERT_EQUAL(105, r1.get_sat_count());
  // Average precision
  TEST_ASSERT_EQUAL_FLOAT(7, r1.get_precision());

}

/**
 * Test merging of multiple merging
 */
void reading_merging_multiple(void) {
  const char* reading_str1 = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5681.7188,N,1411.8420,E,9861.20,A,109,9*46";
  const char* reading_str2 = "$BNRDD,2041,2012-09-20T16:54:58Z,796,83,33915,A,5611.7666,N,1399.8100,E,9761.00,A,101,5*11";
  const char* reading_str3 = "$BNRDD,2041,2012-09-20T16:55:58Z,762,77,33955,A,5531.7373,N,1451.8611,E,9661.05,A,91,9*41";
  const char* reading_str4 = "$BNRDD,2041,2012-09-20T16:56:58Z,780,73,33985,A,5611.7771,N,1311.8815,E,9561.08,A,85,9*19";

  Reading r1(reading_str1);
  Reading r2(reading_str2);
  Reading r3(reading_str3);
  Reading r4(reading_str4);

  r1 += r2;
  r1 += r3;
  r1 += r4;

  // Same device id
  TEST_ASSERT_EQUAL(2041, r1.get_device_id());
  // Latest datetime
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:56:58Z", r1.get_iso_timestr());
  // Average cpm
  TEST_ASSERT_EQUAL(778, r1.get_cpm());
  // Average cpb
  TEST_ASSERT_EQUAL(73, r1.get_cpb());
  // latest total count
  TEST_ASSERT_EQUAL(33985, r1.get_total_count());
  // Average latitude
  double avg_lat = (dm_to_dd(5681.7188) + dm_to_dd(5611.7666) + dm_to_dd(5531.7373) + dm_to_dd(5611.7771)) / 4;
  TEST_ASSERT_EQUAL_FLOAT(avg_lat, r1.get_latitude());
  // Average longitude
  double avg_long = (dm_to_dd(1411.8420) + dm_to_dd(1399.8100) + dm_to_dd(1451.8611) + dm_to_dd(1311.8815)) / 4;
  TEST_ASSERT_EQUAL_FLOAT(avg_long, r1.get_longitude());
  // Average altitude
  double avg_alt = (9861.20 + 9761.00 + 9661.05 + 9561.08) / 4;
  TEST_ASSERT_EQUAL_FLOAT(avg_alt, r1.get_altitude());
  // Average satellite count
  TEST_ASSERT_EQUAL(96, r1.get_sat_count());
  // Average precision
  TEST_ASSERT_EQUAL_FLOAT(8, r1.get_precision());
}

/**
 * Test merging of multiple merging with some failed readings
 */
void reading_merging_multiple_faulty(void) {
  const char* reading_str1 = "$BNRDD,2041,2012-09-20T16:53:58Z,500,60,33895,A,5681.7188,N,1411.8420,E,9861.20,A,109,9*46";
  const char* reading_str2 = "$BNRDD,2041,2012-09-20T16:54:58Z,0,0,33895,V,0000.0000,N,0000.0000,E,0000.00,V,101,5*11";
  const char* reading_str3 = "$BNRDD,2041,2012-09-20T16:55:58Z,0,0,33895,V,5531.7373,N,1451.8611,E,9661.05,A,91,9*41";
  const char* reading_str4 = "$BNRDD,2041,2012-09-20T16:56:58Z,700,80,33995,A,0000.0000,N,0000.0000,E,0000.00,V,85,9*19";

  Reading r1(reading_str1);
  Reading r2(reading_str2);
  Reading r3(reading_str3);
  Reading r4(reading_str4);

  r1 += r2;
  r1 += r3;
  r1 += r4;

  // Same device id
  TEST_ASSERT_EQUAL(2041, r1.get_device_id());
  // Latest datetime
  TEST_ASSERT_EQUAL_STRING("2012-09-20T16:56:58Z", r1.get_iso_timestr());
  // Average cpm
  TEST_ASSERT_EQUAL(550, r1.get_cpm());
  // Average cpb
  TEST_ASSERT_EQUAL(65, r1.get_cpb());
  // latest total count
  TEST_ASSERT_EQUAL(33995, r1.get_total_count());
  // Average latitude
  double avg_lat = (dm_to_dd(5681.7188) * 2 + dm_to_dd(5531.7373)) / 3;
  TEST_ASSERT_EQUAL_FLOAT(avg_lat, r1.get_latitude());
  // Average longitude
  double avg_long = (dm_to_dd(1411.8420) * 2 + dm_to_dd(1451.8611)) / 3;
  TEST_ASSERT_EQUAL_FLOAT(avg_long, r1.get_longitude());
  // Average altitude
  double avg_alt = (9861.20 * 2 + 9661.05) / 3;
  TEST_ASSERT_EQUAL_FLOAT(avg_alt, r1.get_altitude());
  // Average satellite count
  TEST_ASSERT_EQUAL(96, r1.get_sat_count());
  // Average precision
  TEST_ASSERT_EQUAL_FLOAT(8, r1.get_precision());
}

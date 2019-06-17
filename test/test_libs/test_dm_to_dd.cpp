#include <unity.h>
#include <dms_dd.h>


/**
 * Test dm to dd
 * values from https://www.rapidtables.com/convert/number/degrees-minutes-seconds-to-degrees.html
 */
void test_dm_to_dd(void) {
  float dm = 3015.50;
  float dd = dm_to_dd(dm);
  TEST_ASSERT_EQUAL_FLOAT(30.25833, dd);

  dm = -3015.50;
  dd = dm_to_dd(dm);
  TEST_ASSERT_EQUAL_FLOAT(-30.25833, dd);
}

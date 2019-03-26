#include <unity.h>
#include <dms_dd.h>


/**
 * Test dd to dms
 * values from https://www.rapidtables.com/convert/number/degrees-minutes-seconds-to-degrees.html
 */
void test_dms_to_dd(void) {
  float dms = 3015.50;
  float dd = dms_to_dd(dms);
  TEST_ASSERT_EQUAL_FLOAT(30.26388, dd);
}

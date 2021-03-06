#include <unity.h>
#include <reading.h>

/**
 * Test a valid reading as json
 */
void reading_json_stationary(void) {
  const char* valid_str = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,5641.7788,N,1411.8820,E,9861.20,A,109,9*46";

  Reading r(valid_str);

  TEST_ASSERT(r.valid_reading());

  char json_buffer[200];

  TEST_ASSERT_TRUE(r.as_json(json_buffer));

  TEST_ASSERT_EQUAL_STRING(
      "{\"captured_at\":\"2012-09-20T16:53:58Z\","
      "\"device_id\":62041,"
      "\"value\":776,"
      "\"unit\":\"cpm\","
      "\"longitude\":14.19803,"
      "\"latitude\":56.69631}\n", json_buffer);

}


/**
 * Test a valid mobile reading as json
 *
 * Currently unused due to removed feature
 */
void reading_json_mobile(void) {
//  const char* valid_str = "$BNRDD,2041,2012-09-20T16:53:58Z,776,63,33895,A,-5641.7788,N,-1411.8820,E,9861.20,A,109,9*46";
//
//  Reading r(valid_str);
//
//  TEST_ASSERT_EQUAL(ReadingValidity::e_valid, r.get_validity());
//
//  char json_buffer[200];
//
//  TEST_ASSERT_TRUE(r.as_json(json_buffer, false));
//
//  TEST_ASSERT_EQUAL_STRING(
//      "{\"captured_at\":\"2012-09-20T16:53:58Z\","
//      "\"device_id\":2041,"
//      "\"value\":776,"
//      "\"unit\":\"cpm\","
//      "\"longitude\":-14.1188,"
//      "\"latitude\":-56.4177}\n", json_buffer);
//
}

/**
 * Test an invalid reading as json
 */
void reading_json_invalid(void) {
  const char* invalid_str = "$BNRDD,2041,2012-09-20T16:53:58Z";

  Reading r(invalid_str);

  TEST_ASSERT_FALSE(r.valid_reading());

  char json_buffer[200];

  TEST_ASSERT_FALSE(r.as_json(json_buffer));
}
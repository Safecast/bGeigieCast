#include <Arduino.h>
#include <unity.h>

#include <circular_buffer.h>

/**
 * Test circular buffer
 */
void test_int_buffer() {
  using buffer_t = int;
  const buffer_t BUFFER_SIZE = 10;
  const buffer_t INVALID_VAL = -1;
  CircularBuffer<buffer_t, BUFFER_SIZE, INVALID_VAL> int_buffer_10;

  TEST_ASSERT_TRUE(int_buffer_10.empty());
  TEST_ASSERT_EQUAL(int_buffer_10.get(), INVALID_VAL);

  buffer_t some_val = 42;

  int_buffer_10.add(some_val);

  TEST_ASSERT_EQUAL(int_buffer_10.get_count(), 1);
  TEST_ASSERT_TRUE(!int_buffer_10.empty());
  TEST_ASSERT_EQUAL(int_buffer_10.get(), some_val);
  TEST_ASSERT_TRUE(int_buffer_10.empty());

  // Fill buffer
  for(buffer_t i = some_val; i < some_val + BUFFER_SIZE; ++i) {
    int_buffer_10.add(i);
  }

  TEST_ASSERT_EQUAL(int_buffer_10.get_count(), BUFFER_SIZE);

  // First should be same as some_val
  TEST_ASSERT_EQUAL(int_buffer_10.get(), some_val);
  TEST_ASSERT_EQUAL(int_buffer_10.get(), some_val + 1);

  TEST_ASSERT_EQUAL(int_buffer_10.get_count(), BUFFER_SIZE - 2);

  // Empty buffer
  while(!int_buffer_10.empty()) {
    int_buffer_10.get();
  }

  // Fill buffer again
  for(buffer_t i = some_val; i < some_val + BUFFER_SIZE; ++i) {
    int_buffer_10.add(i);
  }

  TEST_ASSERT_EQUAL(int_buffer_10.get_count(), BUFFER_SIZE);

  // Add another value
  buffer_t another_val = 12;
  int_buffer_10.add(another_val);

  // should replace the first one because buffer is circular
  TEST_ASSERT_EQUAL(int_buffer_10.get_count(), BUFFER_SIZE);

  // Clear buffer of all except last
  for(buffer_t i = 0; i < BUFFER_SIZE - 1; ++i) {
    TEST_ASSERT_EQUAL(int_buffer_10.get(), some_val + 1 + i);
  }

  TEST_ASSERT_EQUAL(int_buffer_10.get(), another_val);
}

void setup() {
  delay(2000);
  // Unit test start
  UNITY_BEGIN();

  RUN_TEST(test_int_buffer);

  // Unit test done
  UNITY_END();
}

void loop() {
}
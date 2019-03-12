#include <Arduino.h>
#include <unity.h>

#include <web_server/http_request.h>

HttpRequest request;


void test_param_parse_OK(void) {
  const int result_size = 40;
  const char* line = "POST /hello?password=test HTTP1.1";
  char result[result_size];

  request.set_request_line(line);
  TEST_ASSERT_TRUE(request.has_query_params());

  TEST_ASSERT_TRUE(request.get_param_value("password", result, result_size));
  TEST_ASSERT_EQUAL_STRING("test", result);
}


void test_param_parse_empty(void) {
  const int result_size = 40;
  const char* line = "POST /hello?password= HTTP1.1";
  char result[result_size];

  request.set_request_line(line);
  TEST_ASSERT_TRUE(request.has_query_params());

  TEST_ASSERT_TRUE(request.get_param_value("password", result, result_size));
  TEST_ASSERT_EQUAL_STRING("", result);
}


void test_param_parse_too_long(void) {
  const int result_size = 10;
  const char* line = "POST /hello?password=toolongpasswordforsize HTTP1.1";
  char result[result_size];

  request.set_request_line(line);

  TEST_ASSERT_TRUE(request.get_param_value("password", result, result_size));
  TEST_ASSERT_EQUAL_STRING("toolongpa", result);
}

void test_param_parse_multiple(void) {
  const int result_size = 40;
  const char* line = "POST /hello?password=test&ssid=safecast HTTP1.1";
  char result[result_size];

  request.set_request_line(line);

  TEST_ASSERT_TRUE(request.get_param_value("password", result, result_size));
  TEST_ASSERT_EQUAL_STRING("test", result);
  result[0] = '\0';
  TEST_ASSERT_TRUE(request.get_param_value("ssid", result, result_size));
  TEST_ASSERT_EQUAL_STRING("safecast", result);
}


void test_param_parse_missing(void) {
  const int result_size = 40;
  const char* line = "POST /hello?password=test&ssid=safecast HTTP1.1";
  char result[result_size];

  request.set_request_line(line);

  TEST_ASSERT_FALSE(request.get_param_value("api_key", result, result_size));
}


void test_param_parse_full(void) {
  const int result_size = 64;
  const char* line = "GET /save?ssid=Loftwork+COOOP3+Free&password=&apikey=YE_KEY&devsrv=on HTTP/1.1";
  char result[result_size];

  request.set_request_line(line);

  TEST_ASSERT_TRUE(request.get_param_value("ssid", result, result_size));
  TEST_ASSERT_EQUAL_STRING("Loftwork COOOP3 Free", result);
  TEST_ASSERT_TRUE(request.get_param_value("password", result, result_size));
  TEST_ASSERT_EQUAL_STRING("", result);
  TEST_ASSERT_TRUE(request.get_param_value("apikey", result, result_size));
  TEST_ASSERT_EQUAL_STRING("YE_KEY", result);
  TEST_ASSERT_TRUE(request.get_param_value("devsrv", result, result_size));
  TEST_ASSERT_EQUAL_STRING("on", result);
}

void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(test_param_parse_OK);
  RUN_TEST(test_param_parse_empty);
  RUN_TEST(test_param_parse_too_long);
  RUN_TEST(test_param_parse_multiple);
  RUN_TEST(test_param_parse_missing);
  RUN_TEST(test_param_parse_full);

  UNITY_END();
}

void loop() {
}

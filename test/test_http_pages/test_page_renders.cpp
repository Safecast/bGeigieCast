#include <unity.h>
#include <http_pages.h>

void test_render_home_page() {
  TEST_ASSERT_NOT_NULL(HttpPages::get_home_page(
    1234
  ));
}

void test_render_update_page() {
  TEST_ASSERT_NOT_NULL(HttpPages::get_update_page(
    1234
  ));
}

void test_render_config_device_page() {
  TEST_ASSERT_NOT_NULL(HttpPages::get_config_device_page(
      false,
      1234,
      0,
      false
  ));
  TEST_ASSERT_NOT_NULL(HttpPages::get_config_device_page(
      true,
      1234,
      100,
      true
  ));
}

void test_render_config_connection_page() {
  TEST_ASSERT_NOT_NULL(HttpPages::get_config_connection_page(
      false,
      1234,
      "some ap password",
      "some wifi ssid",
      "some wifi password",
      "some pai key",
      false,
      false
  ));
  TEST_ASSERT_NOT_NULL(HttpPages::get_config_connection_page(
      true,
      1234,
      "new ap password",
      "new wifi ssid",
      "new wifi password",
      "new pai key",
      true,
      true
  ));
}

void test_render_config_location_page() {
  TEST_ASSERT_NOT_NULL(HttpPages::get_config_location_page(
      false,
      1234,
      false,
      0,
      0,
      0,
      0
  ));
  TEST_ASSERT_NOT_NULL(HttpPages::get_config_location_page(
      true,
      1234,
      true,
      -123.45678,
      123.45678,
      -123.45678,
      123.45678
  ));
}

void test_pure_css() {
  TEST_ASSERT_NOT_NULL(HttpPages::pure_css);
}

void test_favicon() {
  TEST_ASSERT_NOT_NULL(HttpPages::favicon);
}

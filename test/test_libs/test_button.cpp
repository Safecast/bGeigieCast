#include <Arduino.h>
#include <unity.h>

#include <button.h>
#include <button_observer.h>
#include <user_config.h>

int button_pin = MODE_BUTTON_PIN;

volatile bool button_down = false;
volatile bool button_released = false;
volatile bool button_pressed = false;

volatile bool fn_button_down = false;
volatile bool fn_button_released = false;
volatile bool fn_button_pressed = false;

volatile uint32_t pressed_time = 0;
volatile uint32_t fn_pressed_time = 0;

/**
 * Mock observer for testing
 */
class MockObserver: public ButtonObserver {
  void on_button_down(Button* button) override {
    button_down = true;
  };

  void on_button_release(Button* button) override {
    button_released = true;
  };

  void on_button_pressed(Button* button, uint32_t millis_pressed) override {
    button_pressed = true;
    pressed_time = millis_pressed;
  };
};

//// Functions for testing the callback of the button
void on_button_down_fn(Button* button){
  fn_button_down = true;
}
void on_button_release_fn(Button* button){
  fn_button_released = true;
}
void on_button_pressed_fn(Button* button, uint32_t millis_pressed){
  fn_button_pressed = true;
  fn_pressed_time = millis_pressed;
}

/**
 * Test button and observer class
 *
 * Note... If there is a button connected, dont press it while running the test...
 */
void test_button() {
  Button test_button(button_pin);
  MockObserver o;

  // Set observer class
  test_button.set_observer(&o);

  // Set observer functions
  test_button.set_on_button_down_fn(&on_button_down_fn);
  test_button.set_on_button_release_fn(&on_button_release_fn);
  test_button.set_on_button_pressed_fn(&on_button_pressed_fn);

  TEST_ASSERT_FALSE(test_button.currently_pressed());

  TEST_ASSERT_FALSE(button_down);
  TEST_ASSERT_FALSE(button_released);
  TEST_ASSERT_FALSE(button_pressed);

  TEST_ASSERT_FALSE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);
  TEST_ASSERT_FALSE(fn_button_pressed);

  TEST_ASSERT_TRUE(test_button.state_changed(HIGH));

  TEST_ASSERT_TRUE(test_button.currently_pressed());

  TEST_ASSERT_TRUE(button_down);
  TEST_ASSERT_FALSE(button_released);
  TEST_ASSERT_FALSE(button_pressed);

  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);
  TEST_ASSERT_FALSE(fn_button_pressed);

  // Debounce timer should ignore this
  TEST_ASSERT_FALSE(test_button.state_changed(LOW));
  TEST_ASSERT_FALSE(test_button.state_changed(HIGH));

  TEST_ASSERT_TRUE(button_down);
  TEST_ASSERT_FALSE(button_released);
  TEST_ASSERT_FALSE(button_pressed);

  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);
  TEST_ASSERT_FALSE(fn_button_pressed);

  int wait_time = DEBOUNCE_TIME_MILLIS + 10;

  // Delay for debounce
  delay(wait_time);

  test_button.state_changed(LOW);

  TEST_ASSERT_FALSE(test_button.currently_pressed());

  TEST_ASSERT_TRUE(button_down);
  TEST_ASSERT_TRUE(button_released);
  TEST_ASSERT_TRUE(button_pressed);

  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_TRUE(fn_button_released);
  TEST_ASSERT_TRUE(fn_button_pressed);

  int slack = 10;

  TEST_ASSERT_GREATER_THAN(wait_time, pressed_time);
  TEST_ASSERT_LESS_THAN(wait_time + slack, pressed_time);
  TEST_ASSERT_GREATER_THAN(wait_time, fn_pressed_time);
  TEST_ASSERT_LESS_THAN(wait_time + slack, fn_pressed_time);
}

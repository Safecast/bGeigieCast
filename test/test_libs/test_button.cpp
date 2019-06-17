#include <Arduino.h>
#include <unity.h>

#include <button.h>

int button_pin = 0;


volatile bool button_down = false;
volatile bool button_released = false;
volatile int button_pressed_count = 0;
volatile uint32_t pressed_time = 0;

/**
 * Mock observer for testing
 */
class MockObserver: public ButtonObserver {
  void on_button_down(Button* button) override {
    button_released = false;
    button_down = true;
  };

  void on_button_release(Button* button) override {
    button_released = true;
    button_down = false;
  };

  void on_button_pressed(Button* button, uint32_t millis_pressed) override {
    button_pressed_count++;
    pressed_time = millis_pressed;
  };
};


volatile bool fn_button_down = false;
volatile bool fn_button_released = false;
volatile int fn_button_pressed_count = 0;
volatile uint32_t fn_pressed_time = 0;

//// Functions for testing the callback of the button
void on_button_down_fn(Button* button){
  fn_button_released = false;
  fn_button_down = true;
}
void on_button_release_fn(Button* button){
  fn_button_released = true;
  fn_button_down = false;
}
void on_button_pressed_fn(Button* button, uint32_t millis_pressed){
  fn_button_pressed_count++;
  fn_pressed_time = millis_pressed;
}



/**
 * Test button status pullup
 */
void test_button_status_pullup() {
  Button test_button(button_pin, PULLUP);
  test_button.activate();

  // Reset button (because hardware interactions at activation)
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());

  // Push button down
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_TRUE(test_button.currently_pressed());

  // Release button
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());
}



/**
 * Test button status pulldown
 */
void test_button_status_pulldown() {
  Button test_button(button_pin, PULLDOWN);
  test_button.activate();

  // Reset button (because hardware interactions at activation)
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());

  // Push button down
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);

  TEST_ASSERT_TRUE(test_button.currently_pressed());

  // Release button
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);

  TEST_ASSERT_FALSE(test_button.currently_pressed());
}



/**
 * Test button and callback functions
 */
void test_button_with_callback_functions() {
  Button test_button(button_pin);

  // Set observer functions
  test_button.set_on_button_down_fn(&on_button_down_fn);
  test_button.set_on_button_release_fn(&on_button_release_fn);
  test_button.set_on_button_pressed_fn(&on_button_pressed_fn);

  test_button.activate();

  // Reset button (because hardware interactions at activation)
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());

  // Push the button down
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);

  // Release after debounce time
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(fn_button_down);
  TEST_ASSERT_TRUE(fn_button_released);
  TEST_ASSERT_EQUAL_INT(fn_button_pressed_count, 1);
}

/**
 * Test button observer class
 */
void test_button_with_observer() {
  Button test_button(button_pin);
  MockObserver o;

  // Set observer class
  test_button.set_observer(&o);

  test_button.activate();

  // Reset button (because hardware interactions at activation)
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());

  // Push the button down
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_TRUE(button_down);
  TEST_ASSERT_FALSE(button_released);

  // Release after debounce time
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(button_down);
  TEST_ASSERT_TRUE(button_released);
  TEST_ASSERT_EQUAL_INT(button_pressed_count, 1);
}


/**
 * Test button debounce
 */
void test_button_debounce() {
  fn_button_pressed_count = 0;
  Button test_button(button_pin);
  test_button.activate();

  // Set observer functions
  test_button.set_on_button_down_fn(&on_button_down_fn);
  test_button.set_on_button_release_fn(&on_button_release_fn);
  test_button.set_on_button_pressed_fn(&on_button_pressed_fn);

  // Reset button (because hardware interactions at activation)
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());

  // Push the button down
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_TRUE(test_button.currently_pressed());
  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);

  // Release before debounce
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS - 1);
  TEST_ASSERT_FALSE(test_button.currently_pressed());
  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);

  // Push again before debounce
  test_button.state_changed(LOW, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS - 1);
  TEST_ASSERT_TRUE(test_button.currently_pressed());
  TEST_ASSERT_TRUE(fn_button_down);
  TEST_ASSERT_FALSE(fn_button_released);

  // Release after debounce time
  test_button.state_changed(HIGH, test_button.get_last_state_change() + BUTTON_DEBOUNCE_TIME_MILLIS);
  TEST_ASSERT_FALSE(test_button.currently_pressed());
  TEST_ASSERT_FALSE(fn_button_down);
  TEST_ASSERT_TRUE(fn_button_released);
  TEST_ASSERT_EQUAL_INT(fn_button_pressed_count, 1);
}

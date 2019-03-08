#include <Arduino.h>
#include <unity.h>

#include <rgb_led.h>
#include <user_config.h>

const int pin_r = RGB_LED_PIN_R;
const int pin_g = RGB_LED_PIN_G;
const int pin_b = RGB_LED_PIN_B;

const int full_brightness = 255;

/**
 * Testing the LED, just look at the pretty colors :-)
 */
void test_rgb_led() {
  RGBLed led(pin_r, pin_g, pin_b);

  RGB all_full{full_brightness, full_brightness, full_brightness};
  RGB all_half{full_brightness / 2, full_brightness / 2, full_brightness / 2};

  led.set(all_full);
  delay(250);
  led.set(all_half);
  delay(250);
  led.off();
  delay(250);
  led.set_r(full_brightness);
  delay(250);
  led.set_r(0);
  led.set_g(full_brightness);
  delay(250);
  led.set_g(0);
  led.set_b(full_brightness);
  delay(250);
  led.set_b(0);
  delay(250);
}

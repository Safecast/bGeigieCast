#ifndef BGEIGIE_POINTCAST_BUTTON_HPP
#define BGEIGIE_POINTCAST_BUTTON_HPP

#include <stdint.h>

class Button {
 public:
  Button(uint8_t pin);
  virtual ~Button() = default;

 private:
  uint8_t pin;
};

#endif //BGEIGIE_POINTCAST_BUTTON_HPP

#ifndef BGEIGIE_POINTCAST_CIRCULARBUFFER_HPP
#define BGEIGIE_POINTCAST_CIRCULARBUFFER_HPP

#include <stdint.h>
#include <Arduino.h>

template<typename T, uint16_t max>
class CircularBuffer {
 public:
  CircularBuffer(): buffer(), count(0), current(0){};
  virtual ~CircularBuffer() = default;

  T get(){
    T val;
    if (!empty()) {
      val = buffer[current];
      --count;
      ++current;
      current %= max;
    }
    return val;
  };

  void add(T val){
    buffer[(current + count) % max] = val;
    if(count < max) {
      ++count;
    }else {
      ++current;
      current %= max;
    }
  };

  bool empty() const{
    return count == 0;
  }
 private:
  T buffer[max - 1];
  uint16_t count;
  uint16_t current;
};

#endif //BGEIGIE_POINTCAST_CIRCULARBUFFER_HPP

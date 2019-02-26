#ifndef BGEIGIE_POINTCAST_CIRCULARBUFFER_HPP
#define BGEIGIE_POINTCAST_CIRCULARBUFFER_HPP

#include <Arduino.h>

/**
 * Simple circular buffer
 * @tparam T: Type of the buffer
 * @tparam max: max items in buffer
 * @tparam null_value: return value if you get but no items are in the buffer
 */
template<typename T, uint16_t max, T null_value = nullptr>
class CircularBuffer {
 public:
  CircularBuffer() : buffer(), count(0), current(0) {};
  virtual ~CircularBuffer() = default;

  T get() {
    if(empty()) {
      return null_value;
    }
    T val = buffer[current];
    --count;
    ++current;
    current %= max;
    return val;
  };

  void add(T val) {
    buffer[(current + count) % max] = val;
    if(count < max) {
      ++count;
    } else {
      ++current;
      current %= max;
    }
  };

  bool empty() const {
    return count == 0;
  }

  uint16_t get_count() const {
    return count;
  }

 private:
  T buffer[max];
  uint16_t count;
  uint16_t current;
};

#endif //BGEIGIE_POINTCAST_CIRCULARBUFFER_HPP

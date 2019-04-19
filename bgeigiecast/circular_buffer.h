#ifndef BGEIGIECAST_CIRCULARBUFFER_HPP
#define BGEIGIECAST_CIRCULARBUFFER_HPP

#include <stdint.h>

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

  /**
   * Get the next value from the buffer, should check if buffer is not empty before calling this
   * @return: next value T or null_value if the buffer is empty
   */
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

  /**
   * Add a value to the buffer. If the buffer is full, it will throw away the oldest value and add this.
   * @param val
   */
  void add(T val) {
    buffer[(current + count) % max] = val;
    if(count < max) {
      ++count;
    } else {
      ++current;
      current %= max;
    }
  };

  /**
   * Check if the buffer is empty
   * @return: true if buffer is empty
   */
  bool empty() const {
    return count == 0;
  }

  /**
   * Get the amount of items in the buffer
   * @return
   */
  uint16_t get_count() const {
    return count;
  }

  /**
   * Clear the buffer
   */
  void clear() {
    count = 0;
  }

 private:
  T buffer[max];
  uint16_t count;
  uint16_t current;
};

#endif //BGEIGIECAST_CIRCULARBUFFER_HPP

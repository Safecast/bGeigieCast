#include "debugger.h"

void debug_begin(unsigned long baud) {
#if ENABLE_DEBUG
  Serial.begin(baud);
  Serial.println();
#endif
}
#ifndef BGEIGIE_POINTCAST_DEBUGGER_H
#define BGEIGIE_POINTCAST_DEBUGGER_H

#include "user_config.h"

#if ENABLE_DEBUG
#include <Arduino.h>
#endif

template<typename T>
void debug_println(T val) {
#if ENABLE_DEBUG
  Serial.println(val);
#endif
}

template<typename T>
void debug_print(T val) {
#if ENABLE_DEBUG
  Serial.print(val);
#endif
}

void debug_begin(unsigned long baud);

#endif //BGEIGIE_POINTCAST_DEBUGGER_H

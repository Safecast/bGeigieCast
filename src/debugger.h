#ifndef BGEIGIE_POINTCAST_DEBUGGER_H
#define BGEIGIE_POINTCAST_DEBUGGER_H

#include "user_config.h"


#ifdef UNIT_TEST
#undef ENABLE_DEBUG
#endif

#if ENABLE_DEBUG
#include <Arduino.h>

#ifndef DEBUG_STREAM
#define DEBUG_STREAM Serial
#endif

#define DEBUG_BEGIN(baud) DEBUG_STREAM.begin(baud)
#define DEBUG_PRINT(val) DEBUG_STREAM.print(val)
#define DEBUG_PRINTLN(val) DEBUG_STREAM.println(val)
#define DEBUG_PRINTF(format, ...) DEBUG_STREAM.println(format, ...)
#define DEBUG_FLUSH() DEBUG_STREAM.flush()

#else

#define DEBUG_BEGIN(...) (void*) 0
#define DEBUG_PRINT(val) (*void) val
#define DEBUG_PRINTLN(val) (*void) val
#define DEBUG_PRINTF(format, ...) (*void) val
#define DEBUG_FLUSH() (*void) 0

#endif


#endif //BGEIGIE_POINTCAST_DEBUGGER_H

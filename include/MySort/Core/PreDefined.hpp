#pragma once
#include <stdint.h>

namespace mysort
{
constexpr uint64_t INSERTION_CUT = 10;
}

#define _HOW_YTRACE "{:>10} {}\n" _YLOG_COLOR_RESET, "[TRACE]"
#define _HOW_YINFO _YLOG_GREEN "{:>10} {}\n" _YLOG_COLOR_RESET, "[INFO]"
#define _HOW_YWARNING _YLOG_YELLOW "{:>10} {}\n" _YLOG_COLOR_RESET, "[WARNING]"
#define _HOW_YERROR _YLOG_RED "{:>10} {}\n" _YLOG_COLOR_RESET, "[ERROR]"
#define _HOW_YCRITICAL _YLOG_CYAN "{:>10} {}\n" _YLOG_COLOR_RESET, "[CRITICAL]"

#include <Yutils/Logger.hpp>
#pragma once
#include <cstdint>
#include <memory>
#include <spdlog/logger.h>

namespace mysort
{
constexpr uint64_t INSERTION_CUT = 10;

extern std::shared_ptr<spdlog::logger> globalLogger;
}  // namespace mysort
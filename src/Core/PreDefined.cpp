#include "MySort/Core/PreDefined.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace mysort
{

// Initialize the global logger
std::shared_ptr<spdlog::logger> globalLogger = spdlog::stdout_color_mt("MySort");

}  // namespace mysort
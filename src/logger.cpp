#include "spdlog/sinks/stdout_color_sinks.h"
#include "logger.hpp"

std::shared_ptr<spdlog::logger> Logger::projectLog;

void Logger::init()
{
    spdlog::set_pattern("%^%v%$");
    projectLog = spdlog::stdout_color_mt("ENGINELOG");
    projectLog->set_level(spdlog::level::trace);
}

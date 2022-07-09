#ifndef LOGGER_HPP
    #define LOGGER_HPP
    #include <memory>
    #include "spdlog/spdlog.h"
    class Logger {
        private: 
            static std::shared_ptr<spdlog::logger> projectLog;
        public:
            static void init();
            inline static std::shared_ptr<spdlog::logger>& GetLogger() {return projectLog;}
    };
    #define INFO(...) Logger::GetLogger()->info(__VA_ARGS__)
    #define WARN(...) Logger::GetLogger()->warn(__VA_ARGS__)
    #define ERROR(...) Logger::GetLogger()->error(__VA_ARGS__); exit(1)
#endif
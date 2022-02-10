//
// Created by egor on 2/7/22.
//
#include "Logger/SpdLogger.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace logger {

    SpdLogger::SpdLogger(): m_logger() {
        spdlog::set_pattern("[%D %H:%M:%S:%f %z] [%^%l%$] [thread %t] %v");

        std::time_t ct = std::time(0);
        std::string logsFileName = std::string("logs/").append(ctime(&ct)).append(".txt");

        m_logger = spdlog::basic_logger_mt("basic_logger", logsFileName);
    }

    void SpdLogger::logInfo(std::string const& payload) const {
        spdlog::info(payload);
        m_logger->info(payload);
    }

    void SpdLogger::logWarning(std::string const& payload) const {
        spdlog::warn(payload);
        m_logger->warn(payload);
    }

    void SpdLogger::logError(std::string const& payload) const {
        spdlog::error(payload);
        m_logger->error(payload);
    }

    void SpdLogger::logCritical(std::string const&payload) const {
        spdlog::critical(payload);
        m_logger->critical(payload);
    }
}


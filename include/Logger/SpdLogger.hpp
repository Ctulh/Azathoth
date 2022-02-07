//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_SPDLOGGER_HPP
#define AZATHOTH_SPDLOGGER_HPP

#include "ILogger.hpp"
#include <spdlog/spdlog.h>
#include <memory>

namespace logger {

    class SpdLogger : public ILogger {
    public:
        explicit SpdLogger();
    public:
        void logInfo(std::string const&) const override;
        void logWarning(std::string const&) const override;
        void logError(std::string const&) const override;
        void logCritical(std::string const&) const override;

    private:
        std::shared_ptr<spdlog::logger> m_logger;
    };


}

#endif //AZATHOTH_SPDLOGGER_HPP

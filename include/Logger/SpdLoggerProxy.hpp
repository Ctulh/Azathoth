//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_SPDLOGGERPROXY_HPP
#define AZATHOTH_SPDLOGGERPROXY_HPP

#include "ILogger.hpp"
#include "SpdLogger.hpp"

namespace logger {

    class SpdLoggerProxy: public ILogger {
    public:
        void logInfo(std::string const&) const override;
        void logWarning(std::string const&) const override;
        void logError(std::string const&) const override;
        void logCritical(std::string const&) const override;
    private:
        static SpdLogger m_logger;
    };

}

#endif //AZATHOTH_SPDLOGGERPROXY_HPP

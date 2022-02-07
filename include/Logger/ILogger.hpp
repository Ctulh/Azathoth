//
// Created by egor on 2/7/22.
//

#ifndef AZATHOTH_LOGGERPROXY_HPP
#define AZATHOTH_LOGGERPROXY_HPP

#include <string>

namespace logger {

    class ILogger {
    public:
        virtual void logInfo(std::string const&) const = 0;
        virtual void logWarning(std::string const&) const = 0;
        virtual void logError(std::string const&) const = 0;
        virtual void logCritical(std::string const&) const = 0;

    public:
        virtual ~ILogger() = default;
    };

}

#endif //AZATHOTH_LOGGERPROXY_HPP

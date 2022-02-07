//
// Created by egor on 2/7/22.
//
#include "Logger/SpdLoggerProxy.hpp"

namespace logger {

    void SpdLoggerProxy::logInfo(std::string const& payload) const {
        m_logger.logInfo(payload);
    }

    void SpdLoggerProxy::logWarning(std::string const& payload) const {
        m_logger.logWarning(payload);
    }

    void SpdLoggerProxy::logError(std::string const& payload) const {
        m_logger.logError(payload);
    }

    void SpdLoggerProxy::logCritical(std::string const& payload) const {
        m_logger.logCritical(payload);
    }

    SpdLogger SpdLoggerProxy::m_logger;
}
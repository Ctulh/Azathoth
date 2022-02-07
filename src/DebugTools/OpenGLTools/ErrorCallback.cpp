//
// Created by egor on 2/7/22.
//
#include "DebugTools/OpenGLTools/ErrorCallback.hpp"
#include "Logger/Logger.hpp"


namespace OpenGLTools {

    void ErrorCallback(int error, const char *msg) {
        std::string errorInfo  =" [" + std::to_string(error) + "] " + msg;
        logger::log_critical(std::string("[OpenGLErrorCallback] ") + errorInfo);
    }

}

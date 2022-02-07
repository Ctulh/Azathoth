//
// Created by egor on 2/7/22.
//
#include "Logger/Logger.hpp"

int main() {
    logger::log_info("test");
    logger::log_warning("test");
    logger::log_error("test");
    logger::log_critical("test");

}
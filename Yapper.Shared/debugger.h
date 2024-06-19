#pragma once
#include <string>
#include <iostream>
#include <cstdarg>
#include <sstream>

namespace Yapper::Shared::Debug {
    class Debugger {
    public:
        static bool doAssert(bool assertion, const std::string& assertionError);
        static void print(const std::string& log);
        static void print(const char* format, ...);
        static void warning(const std::string& log);
        static void error(const std::string& log);
        static void error(const char* format, ...);
    };
}
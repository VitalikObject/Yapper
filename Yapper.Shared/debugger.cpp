#include "debugger.h"

using namespace Yapper::Shared::Debug;

bool Debugger::doAssert(bool assertion, const std::string& assertionError) {
#if _DEBUG
    if (!assertion) {
        error(assertionError);
    }
#endif // DEBUG
    return assertion;
}

void Debugger::print(const std::string& log) {
#if _DEBUG
    std::cout << log << std::endl;
#endif // DEBUG
}

void Debugger::print(const char* format, ...) {
#if _DEBUG
    va_list args;
    va_start(args, format);
    std::ostringstream oss;
    std::vfprintf(stderr, format, args);
    va_end(args);
    std::cout << oss.str() << std::endl;
#endif // DEBUG
}

void Debugger::warning(const std::string& log) {
#if _DEBUG
    std::cerr << "Warning: " + log << std::endl;
#endif // DEBUG
}

void Debugger::error(const std::string& log) {
#if _DEBUG
    std::cerr << "Error: " + log << std::endl;
#endif // DEBUG
}

void Debugger::error(const char* format, ...) {
#if _DEBUG
    va_list args;
    va_start(args, format);
    std::ostringstream oss;
    std::vfprintf(stderr, format, args);
    va_end(args);
    std::cerr << "Error: " << oss.str() << std::endl;
#endif // DEBUG
}
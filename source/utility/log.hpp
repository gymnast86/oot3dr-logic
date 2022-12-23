
#pragma once

#include <string>
#include <list>
#include <fstream>
#include <string.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

class ErrorLog {
private:
    static constexpr size_t MAX_ERRORS = 5;

    std::ofstream output;
    std::list<std::string> lastErrors;

    ErrorLog();
    ~ErrorLog();
public:
    ErrorLog(const ErrorLog&) = delete;
    ErrorLog& operator=(const ErrorLog&) = delete;

    static ErrorLog& getInstance();
    void log(const std::string& msg);
    std::string getLastErrors() const;
    void clearLastErrors();
    void close();
};

class DebugLog {
private:
    std::ofstream output;

    DebugLog();
    ~DebugLog();
public:
    DebugLog(const DebugLog&) = delete;
    DebugLog& operator=(const DebugLog&) = delete;

    static DebugLog& getInstance();
    void log(const std::string& msg);
    void close();
};

void CloseLogs();

#define LOG_TO_ERROR(message) \
    ErrorLog::getInstance().log(std::string(std::string(__FILENAME__) + "::" + TOSTRING(__LINE__)) + std::string(": " + std::string(message)));

#ifdef ENABLE_DEBUG
#define LOG_TO_DEBUG(message) \
    DebugLog::getInstance().log(std::string(std::string(__FILENAME__) + "::" + TOSTRING(__LINE__)) + std::string(": " + std::string(message)));
#else
#define LOG_TO_DEBUG(message)
#endif

#define LOG_AND_RETURN_IF_ERR(func) { \
    if(const auto error = func; error != decltype(error)::NONE) {\
        ErrorLog::getInstance().log(std::string("Encountered error on line " TOSTRING(__LINE__) " of ") + __FILENAME__); \
        return error;  \
    } \
}

#define LOG_ERR_AND_RETURN(error) { \
    ErrorLog::getInstance().log(std::string("Encountered " #error " on line " TOSTRING(__LINE__) " of ") + __FILENAME__); \
    return error; \
}

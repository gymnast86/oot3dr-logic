#include "log.hpp"

#include <iostream>
#include <fstream>

ErrorLog::ErrorLog()
{
    #ifdef ENABLE_DEBUG
        output.open(LOGS_PATH "Error Log.txt");

        output << "Z3DR Version " << RANDOMIZER_VERSION << std::endl;

        output << std::endl << std::endl;
    #endif
}

ErrorLog::~ErrorLog() { }

ErrorLog& ErrorLog::getInstance()
{
    static ErrorLog s_Instance;
    return s_Instance;
}

void ErrorLog::log(const std::string& msg)
{
    output << msg << std::endl;
    lastErrors.push_back(msg);
    if (lastErrors.size() > MAX_ERRORS)
    {
        lastErrors.pop_front();
    }
}

std::string ErrorLog::getLastErrors() const
{
    std::string errStr = "";
    for (auto& error : lastErrors)
    {
        errStr += error + "\n";
    }
    return errStr;
}

void ErrorLog::clearLastErrors()
{
    lastErrors.clear();
}

void ErrorLog::close()
{
    output.close();
}

DebugLog::DebugLog()
{
    #ifdef ENABLE_DEBUG
        output.open(LOGS_PATH "Debug Log.txt");

        output << "Z3DR Version " << RANDOMIZER_VERSION << std::endl;

        output << std::endl << std::endl;
    #endif
}

DebugLog::~DebugLog() { }

DebugLog& DebugLog::getInstance()
{
    static DebugLog s_Instance;
    return s_Instance;
}

void DebugLog::log(const std::string& msg)
{
    #ifdef ENABLE_DEBUG
        output << msg << std::endl;
    #endif
}

void DebugLog::close()
{
    output.close();
}

void CloseLogs()
{
    DebugLog::getInstance().close();
    ErrorLog::getInstance().close();
}

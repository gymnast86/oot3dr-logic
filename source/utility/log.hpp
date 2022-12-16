
#pragma once

#include <string>

void DebugLog(const std::string& msg = "");
void OpenDebugLog(const std::string& seed);
void CloseDebugLog();

#ifdef ENABLE_DEBUG
    #define LOG_TO_DEBUG(msg) DebugLog(msg);
#else
    #define LOG_TO_DEBUG(msg)
#endif

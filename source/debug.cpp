
#include "debug.hpp"
#include "file_system_defs.hpp"

#include <iostream>
#include <fstream>

static std::ofstream logger;

void DebugLog(const std::string& msg /*= ""*/)
{
    #ifdef NON_3DS
        logger << msg << std::endl;
    #endif
}

void PpenDebugLog(const std::string& seed)
{
    #ifdef NON_3DS
        logger.open(LOGS_PATH"/debug_logger" + seed + ".txt");
    #endif
}

void CloseDebugLog()
{
    #ifdef NON_3DS
        logger.close();
    #endif
}

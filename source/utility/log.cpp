
#include "log.hpp"
#include "file_system_defs.hpp"

#include <iostream>
#include <fstream>

std::ofstream logger;

void DebugLog(const std::string& msg /*= ""*/)
{
    #ifdef NON_3DS
        if (logger.is_open())
        {
            logger << msg << std::endl;
        }
        else
        {
            std::cout << "debug_logger not opened" << std::endl;
        }
    #endif
}

void OpenDebugLog(const std::string& seed)
{
    logger.open(LOGS_PATH"/debug_logger" + seed + ".txt");
}

void CloseDebugLog()
{
    #ifdef NON_3DS
        logger.close();
    #endif
}

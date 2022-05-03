#pragma once

#ifdef NON_3DS
    #define ROMFS "../romfs"
    #define LOGS_PATH "./logs"
#endif

#ifndef NON_3DS
    #define ROMFS "romfs:"
    #define LOGS_PATH "/3ds/logs"
#endif

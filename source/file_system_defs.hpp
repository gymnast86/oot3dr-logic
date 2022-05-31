#pragma once

#ifdef NON_3DS
    #define ROMFS "../romfs"
    #define LOGS_PATH "./logs"
    #define WORLD_GRAPHS "../local_testing/logs"
#endif

#ifndef NON_3DS
    #define ROMFS "romfs:"
    #define LOGS_PATH "/3ds/logs"
    #define WORLD_GRAPHS "/3ds/logs"
#endif

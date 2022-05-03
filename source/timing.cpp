#include "timing.hpp"
#include <iostream>

// TIMING FOR LOCAL SYSTEM TESTING
#ifdef NON_3DS
    #include <chrono>

    static std::chrono::time_point<std::chrono::high_resolution_clock> start;
    static std::chrono::time_point<std::chrono::high_resolution_clock> end;

    void StartTiming()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    void EndTiming()
    {
        end = std::chrono::high_resolution_clock::now();
    }

    void PrintTiming()
    {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        auto seconds = static_cast<double>(duration.count()) / 1000000.0f;
        std::cout << "Timing took " << std::to_string(seconds) << " seconds" << std::endl;
    }
#endif

// TIMING FOR 3DS SYSTEM
#ifndef NON_3DS
    #include <3ds.h>

    #define TICKS_PER_SEC 268123480.0

    static u64 start;
    static u64 end;

    void StartTiming()
    {
        start = svcGetSystemTick();
    }

    void EndTiming()
    {
        end = svcGetSystemTick();
    }

    void PrintTiming()
    {
        double seconds = (end - start)/TICKS_PER_SEC;
        std::cout << "Timing took " << std::to_string(seconds) << " seconds" << std::endl;
    }
#endif

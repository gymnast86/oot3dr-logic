#include "timing.hpp"
#include <iostream>
#include <unordered_map>

// TIMING FOR LOCAL SYSTEM TESTING
#ifdef NON_3DS
    #include <chrono>

    struct TimingStruct {
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
    };

    static std::unordered_map<std::string, TimingStruct> timers = {};

    void StartTiming(const std::string& name)
    {
        timers[name].start = std::chrono::high_resolution_clock::now();
    }

    void EndTiming(const std::string& name)
    {
        timers[name].end = std::chrono::high_resolution_clock::now();
    }

    double GetTiming(const std::string& name)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now - timers[name].start);
        return static_cast<double>(duration.count()) / 1000000000.0f;
    }

    void PrintTiming(const std::string& name)
    {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timers[name].end - timers[name].start);
        auto seconds = static_cast<double>(duration.count()) / 1000000.0f;
        std::cout << name << " timing took " << std::to_string(seconds) << " seconds" << std::endl;
    }
#endif

// TIMING FOR 3DS SYSTEM
#ifndef NON_3DS
    #include <3ds.h>

    #define TICKS_PER_SEC 268123480.0

    struct TimingStruct {
        u64 start;
        u64 end;
    };

    static std::unordered_map<std::string, TimingStruct> timers = {};

    void StartTiming(const std::string& name)
    {
        timers[name].start = svcGetSystemTick();
    }

    void EndTiming(const std::string& name)
    {
        timers[name].end = svcGetSystemTick();
    }

    double GetTiming(const std::string& name)
    {
        double now = svcGetSystemTick();
        double seconds = (now - timers[name].start)/TICKS_PER_SEC;
        return seconds;
    }

    void PrintTiming(const std::string& name)
    {
        double seconds = (timers[name].end - timers[name].start)/TICKS_PER_SEC;
        std::cout << "Timing took " << std::to_string(seconds) << " seconds" << std::endl;
    }
#endif

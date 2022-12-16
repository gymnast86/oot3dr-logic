#include "timing.hpp"
#include <iostream>
#include <unordered_map>

// TIMING FOR LOCAL SYSTEM TESTING
#ifdef NON_3DS
    #include <chrono>

    struct TimingStruct {
        std::chrono::time_point<std::chrono::high_resolution_clock> lastTimePoint;
        std::chrono::duration<long, std::nano> totalTime;
        bool paused = true;
    };

    static std::unordered_map<std::string, TimingStruct> timers = {};

    void StartTiming(const std::string& name)
    {
        timers[name].lastTimePoint = std::chrono::high_resolution_clock::now();
        timers[name].paused = false;
    }

    void PauseTiming(const std::string& name)
    {
        timers[name].totalTime += std::chrono::high_resolution_clock::now() - timers[name].lastTimePoint;
        timers[name].paused = true;
    }

    void EndTiming(const std::string& name)
    {
        timers[name].totalTime += std::chrono::high_resolution_clock::now() - timers[name].lastTimePoint;
        timers[name].paused = true;
    }

    double GetTiming(const std::string& name)
    {
        timers[name].totalTime += std::chrono::high_resolution_clock::now() - timers[name].lastTimePoint;
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(timers[name].totalTime);
        return static_cast<double>(duration.count()) / 1000000000.0f;
    }

    void PrintTiming(const std::string& name)
    {
        auto duration = timers[name].totalTime;
        auto seconds = static_cast<double>(duration.count()) / 1000000000.0f;
        std::cout << name << " timing took " << std::to_string(seconds) << " seconds" << std::endl;
    }
#endif

// TIMING FOR 3DS SYSTEM
#ifndef NON_3DS
    #include <3ds.h>

    struct TimingStruct {
        u64 lastTimePoint;
        u64 totalTime;
    };

    static std::unordered_map<std::string, TimingStruct> timers = {};

    void StartTiming(const std::string& name)
    {
        timers[name].lastTimePoint = svcGetSystemTick();
    }

    void PauseTiming(const std::string& name)
    {
        timers[name].totalTime += svcGetSystemTick() - timers[name].lastTimePoint;
    }

    void EndTiming(const std::string& name)
    {
        timers[name].totalTime += svcGetSystemTick() - timers[name].lastTimePoint;
    }

    double GetTiming(const std::string& name)
    {
        timers[name].totalTime += svcGetSystemTick() - timers[name].lastTimePoint;
        double seconds = timers[name].totalTime / TICKS_PER_SEC;
        return seconds;
    }

    void PrintTiming(const std::string& name)
    {
        double seconds = timers[name].totalTime / TICKS_PER_SEC;
        std::cout << name << " timing took " << std::to_string(seconds) << " seconds" << std::endl;
    }
#endif

#pragma once

#include <string>

void StartTiming(const std::string& name);
void EndTiming(const std::string& name);
double GetTiming(const std::string& name);
void PrintTiming(const std::string& name);

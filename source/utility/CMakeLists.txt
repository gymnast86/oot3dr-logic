cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0076 NEW)
target_sources(Z3DR PRIVATE log.cpp
                            random.cpp
                            string_util.cpp
                            timing.cpp
                            Yaml.cpp)

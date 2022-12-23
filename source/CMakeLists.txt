cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0076 NEW)
target_sources(Z3DR PRIVATE area_id.cpp
                            area.cpp
                            dungeon.cpp
                            entrance.cpp
                            fill.cpp
                            item_pool.cpp
                            generate.cpp
                            item_id.cpp
                            item.cpp
                            location_id.cpp
                            location.cpp
                            requirement.cpp
                            search.cpp
                            spoiler_log.cpp
                            world.cpp)

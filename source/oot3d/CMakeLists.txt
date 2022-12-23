cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0076 NEW)
target_sources(Z3DR PRIVATE oot3d_area.cpp
                            oot3d_dungeon.cpp
                            oot3d_entrance.cpp
                            oot3d_item.cpp
                            oot3d_location.cpp
                            oot3d_world.cpp
                            oot3d_world_fill.cpp
                            oot3d_world_logic.cpp
                            oot3d_world_item_pool.cpp)

cmake_minimum_required(VERSION 3.7)
project(logic_testing CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -D NON_3DS")

add_executable(logic_testing main.cpp ../source/generate.cpp ../source/timing.cpp ../source/location.cpp ../source/item.cpp
               ../source/area_id.cpp ../source/area.cpp ../source/requirement.cpp ../source/debug.cpp ../source/entrance.cpp
               ../source/world.cpp ../source/oot3d/oot3d_world.cpp ../source/oot3d/oot3d_entrance.cpp ../source/oot3d/oot3d_item.cpp)
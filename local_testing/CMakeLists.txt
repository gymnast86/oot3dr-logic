cmake_minimum_required(VERSION 3.7)
project(logic_testing CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(PythonInterp REQUIRED)

add_custom_target(logic_defs ALL
                  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../source/oot3d/oot3d_world_graph_defs.hpp")

add_custom_command(TARGET logic_defs
                   PRE_BUILD
                   COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../source/oot3d/build_defs.py" "${CMAKE_CURRENT_SOURCE_DIR}/../source/oot3d/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fomit-frame-pointer -ffunction-sections -fno-rtti -fno-exceptions -fno-var-tracking-assignments -Wreorder -DNON_3DS")

add_executable(local_testing main.cpp ../source/area_id.cpp
                                      ../source/area.cpp
                                      ../source/debug.cpp
                                      ../source/entrance.cpp
                                      ../source/fill.cpp
                                      ../source/generate.cpp
                                      ../source/item.cpp
                                      ../source/location.cpp
                                      ../source/logic.cpp
                                      ../source/random.cpp
                                      ../source/requirement.cpp
                                      ../source/search.cpp
                                      ../source/timing.cpp
                                      ../source/world.cpp
                                      ../source/oot3d/oot3d_area.cpp
                                      ../source/oot3d/oot3d_entrance.cpp
                                      ../source/oot3d/oot3d_item_pool.cpp
                                      ../source/oot3d/oot3d_world.cpp
                                      ../source/oot3d/oot3d_item.cpp
                                      ../source/oot3d/oot3d_location.cpp
                                      ../source/oot3d/oot3d_logic.cpp
                                      ../source/oot3d/oot3d_world_graph.cpp
                                      ../source/oot3d/oot3d_world_logic.cpp
)

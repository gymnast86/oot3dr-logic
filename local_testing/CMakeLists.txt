cmake_minimum_required(VERSION 3.21)
project(Z3DR CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PythonInterp REQUIRED)
add_custom_target(logic_data ALL)
add_custom_command(TARGET logic_data
                  PRE_BUILD
                  COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../source/build_ids.py" "${CMAKE_CURRENT_SOURCE_DIR}/../source/")
add_custom_command(OUTPUT ../source/item_id.cpp ../source/area_id.cpp ../source/location_id.cpp
                   COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../source/build_ids.py" "${CMAKE_CURRENT_SOURCE_DIR}/../source/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreorder -DNON_3DS")

if(ENABLE_DEBUG)
 message("Debugging is ON")
 add_compile_definitions(ENABLE_DEBUG)
 add_compile_options(-g -O0)
else()
 add_compile_options(-O3)
endif()

add_executable(Z3DR main.cpp)

add_subdirectory("../source" "source")
add_subdirectory("../source/oot3d" "source/oot3d")
add_subdirectory("../source/utility" "source/utility")

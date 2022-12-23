cmake_minimum_required(VERSION 3.21)
project(Z3DR CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Generate header files for areas, items, and locations
find_package(PythonInterp REQUIRED)
execute_process(COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../source/build_ids.py" "${CMAKE_CURRENT_SOURCE_DIR}/../source/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreorder")

if(ENABLE_DEBUG)
 message("Debugging is ON")
 add_compile_definitions(ENABLE_DEBUG)
 add_compile_options(-g -O0)
else()
 add_compile_options(-Ofast)
endif()

file(COPY "../romfs" DESTINATION "${CMAKE_BINARY_DIR}")
add_compile_definitions(ROMFS="./romfs/" LOGS_PATH="./")
add_compile_definitions(RANDOMIZER_VERSION="1.0")

add_executable(Z3DR ../source/main.cpp)

add_subdirectory("../source" "source")
add_subdirectory("../source/oot3d" "source/oot3d")
add_subdirectory("../source/utility" "source/utility")

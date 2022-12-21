cmake_minimum_required(VERSION 3.21)

project(Z3DR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Generate header files for areas, items, and locations
find_package(PythonInterp REQUIRED)
execute_process(COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/../source/build_ids.py" "${CMAKE_CURRENT_SOURCE_DIR}/../source/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreorder -DNON_3DS")

if(ENABLE_DEBUG)
  message("Debugging is ON")
  add_compile_definitions(ENABLE_DEBUG)
  add_compile_options(-g -O0)
else()
  add_compile_options(-O3)
endif()

file(COPY "../romfs" DESTINATION "${CMAKE_BINARY_DIR}")
add_compile_definitions(ROMFS="./romfs/" LOGS_PATH="./")
add_compile_definitions(RANDOMIZER_VERSION="1.0")

# Qt Stuff
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Z3DR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Z3DR APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Z3DR SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Z3DR
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Z3DR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Z3DR PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Z3DR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

add_subdirectory("../source" "source")
add_subdirectory("../source/oot3d" "source/oot3d")
add_subdirectory("../source/utility" "source/utility")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Z3DR)
endif()

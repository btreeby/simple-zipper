# Call with the following syntax:
#     cmake -B builds '.' -DQt5_DIR="C:\path\to\Qt\lib\cmake\Qt5"
#     cmake --build builds/ --config Debug

cmake_minimum_required(VERSION 3.21)

# set the project name and version
project(SimpleZipperApp VERSION 1.0)

# set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find the Qt packages
find_package(Qt5 COMPONENTS Core Widgets Gui Test REQUIRED)

# include directories
include_directories("src" "test" "miniz")

# run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# suppress ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION true)

# source files
FILE(GLOB SOURCES "src/*.*")
FILE(GLOB MINIZ_SOURCES "miniz/*.*")
FILE(GLOB TEST_SOURCES "test/*.*")

####################
# MAIN APPLICATION #
####################

set(SOURCES
    "src/main.cxx"
    "src/SimpleZipper.cxx"
    "src/SimpleZipper.h"
    "src/SimpleZipperUI.cxx"
    "src/SimpleZipperUI.h"
    "miniz/miniz.c"
    "miniz/miniz.h"
)

# add the GUI application executable
add_executable(SimpleZipperApp ${SOURCES})

# link the Qt5 widgets library to the GUI application
target_link_libraries(SimpleZipperApp PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui)

####################
# TEST APPLICATION #
####################

set(TEST_SOURCES
    "src/SimpleZipper.cxx"
    "src/SimpleZipper.h"
    "miniz/miniz.c"
    "miniz/miniz.h"
    "test/TestSimpleZipper.h"
)

# create the test executable
enable_testing(true)
add_executable(TestSimpleZipper ${TEST_SOURCES})
add_test(NAME TestSimpleZipper COMMAND TestSimpleZipper)

# link the Qt5 core and test libraries to the test
target_link_libraries(TestSimpleZipper PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Test)

####################

# set the output directories
set_target_properties(SimpleZipperApp TestSimpleZipper PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
)

# set the Visual Studio startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SimpleZipperApp)

# create a command to copy the required Qt dlls to the build directory
add_custom_command(TARGET SimpleZipperApp POST_BUILD
    COMMAND "${Qt5_DIR}/../../../bin/windeployqt.exe" $<TARGET_FILE:SimpleZipperApp>
    COMMENT "Copying Qt dlls to the build directory")

add_custom_command(TARGET TestSimpleZipper POST_BUILD
    COMMAND "${Qt5_DIR}/../../../bin/windeployqt.exe" $<TARGET_FILE:TestSimpleZipper>
    COMMENT "Copying Qt dlls to the build directory")

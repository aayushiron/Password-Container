cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(password-container)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES src/core/password_container.cc src/core/util.cc)

list(APPEND CLI_SOURCE_FILES src/cli/command_line_input.cc src/cli/argument_parser.cc)

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}   ${CLI_SOURCE_FILES}
        src/gui/password_container_app.cc)

list(APPEND TEST_FILES tests/test_password_container.cc tests/test_util.cc tests/test_command_line_input.cc tests/test_argument_parser.cc)

add_executable(password-container-cli apps/password_container_cli_main.cc ${CORE_SOURCE_FILES} ${CLI_SOURCE_FILES})
target_include_directories(password-container-cli PRIVATE include)

ci_make_app(
        APP_NAME        password-container-app
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/password-container-main.cc ${SOURCE_FILES}
        INCLUDES        include
        BLOCKS          Cinder-ImGui
)

ci_make_app(
        APP_NAME        password-container-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2
        BLOCKS          Cinder-ImGui
)

if(MSVC)
    set_property(TARGET password-container-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()
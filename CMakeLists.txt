cmake_minimum_required(VERSION 3.30)

project(cclox VERSION 0.1
        DESCRIPTION "C++ Bytecode Virtual Machine"
        LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
        src/main.cc
        src/chunk.cc
        src/debug.cc
        src/vm.cc
)

add_executable(cclox ${SOURCES})

target_include_directories(cclox PUBLIC
    ${CMAKE_HOME_DIRECTORY}/src/include
)

# Enable debug mode if specified
option(DEBUG_TRACE_EXECUTION "Enable debug trace execution" OFF)

if(DEBUG_TRACE_EXECUTION)
    add_definitions(-DDEBUG_TRACE_EXECUTION)
    message(STATUS "Debug mode enabled: DEBUG_TRACE_EXECUTION")
endif()

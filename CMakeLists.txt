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
)

add_executable(cclox ${SOURCES})

target_include_directories(cclox PUBLIC
    ${CMAKE_HOME_DIRECTORY}/src/include
)
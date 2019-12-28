cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(dhcp-client VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_COMPILER "gcc")

file(GLOB SOURCES "**/*.h" "**/*.c")
message(SOURCES are ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
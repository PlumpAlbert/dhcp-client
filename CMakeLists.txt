cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(dhcp-client VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_COMPILER "gcc")

add_executable(dhcp-client include/dhcp.h include/helpers.h include/dhcp-client.h src/dhcp-client.c src/main.c src/helpers.c include/dhcp_option.h)
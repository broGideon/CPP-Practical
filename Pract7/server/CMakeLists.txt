cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 26)

add_executable(server main.cpp)
target_link_libraries(server ws2_32)
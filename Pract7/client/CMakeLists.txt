cmake_minimum_required(VERSION 3.28)
project (client)

set(CMAKE_CXX_STANDARD 26)

add_executable(client main.cpp)
target_link_libraries(client ws2_32)
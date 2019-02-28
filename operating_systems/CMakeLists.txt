cmake_minimum_required(VERSION 2.8)
project(operating_systems)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

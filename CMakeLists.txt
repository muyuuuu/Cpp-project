cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

message(STATUS "======= ${PROJECT_SOURCE_DIR}")
# 头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

message(STATUS "======= ${CMAKE_CURRENT_SOURCE_DIR}")
# 源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(main ${SRC_LIST} main.cpp)
cmake_minimum_required(VERSION 3.24...3.30)
project(string-span-lib LANGUAGES CXX)

add_library(strspan INTERFACE)

target_include_directories(strspan INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

cmake_minimum_required(VERSION 3.24)
project(string-span-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_executable(string-span-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
)

target_link_libraries(string-span-tests PRIVATE
    GTest::gtest_main
    strspan
)

target_compile_options(string-span-tests PRIVATE
    -Wno-write-strings
)

enable_testing()
gtest_discover_tests(string-span-tests)

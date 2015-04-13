cmake_minimum_required(VERSION 2.8)

project(routing_tests)

include_directories(${routing_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include)

add_executable(routing_tests
    RegexpConverterTests.cpp
    StringTokenizerTests.cpp
    PathParserTests.cpp
    RouterTests.cpp
)

target_link_libraries(routing_tests gtest_main routing)

add_test(test1 routing_tests)
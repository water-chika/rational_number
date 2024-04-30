cmake_minimum_required(VERSION 3.20)

project(rational_number)

add_library(rational_number
    rational_number.hpp
    rational_number.cpp)

target_include_directories(rational_number PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(rational_number PROPERTIES CXX_STANDARD 23)

add_executable(rational_number_test
    main.cpp)

set_target_properties(rational_number_test PROPERTIES CXX_STANDARD 23)

target_link_libraries(rational_number_test PUBLIC rational_number)

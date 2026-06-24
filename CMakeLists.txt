cmake_minimum_required(VERSION 3.12)
project(ECV)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    test_data_management
    tests/test_data_management.cpp
    src/core/content.cpp
    src/services/content_manager.cpp
    )

add_executable(
    test_get_data
    tests/test_get_data.cpp
    src/core/content.cpp
    src/services/content_manager.cpp
    )
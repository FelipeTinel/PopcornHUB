cmake_minimum_required(VERSION 3.12)
project(ECV)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    test_content_save
    tests/test_content_save.cpp
    src/services/user_manager.cpp
    src/services/comment_manager.cpp
    src/services/content_manager.cpp
    src/core/user.cpp
    src/core/comment.cpp
    src/core/content.cpp
)
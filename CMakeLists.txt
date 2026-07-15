cmake_minimum_required(VERSION 3.12)
project(ECV)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(glfw3 REQUIRED)

set(IMGUI_DIR "thirdparty/imgui")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(ECV
    tests/test_ui.cpp
    src/ui/window.cpp
    src/services/auth_service.cpp
    src/services/interaction_service.cpp
    src/services/user_manager.cpp
    src/services/comment_manager.cpp
    src/services/content_manager.cpp
    src/core/user.cpp
    src/core/comment.cpp
    src/core/content.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(ECV PRIVATE
    include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(ECV PRIVATE
    glfw
    OpenGL::GL
)
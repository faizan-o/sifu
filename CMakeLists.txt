
cmake_minimum_required(VERSION 3.20)

project(ImGUI-Example LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW - build from source
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)

# GLAD 2
add_library(glad STATIC
    vendor/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    vendor/glad/include
)

# Dear ImGui
add_library(imgui STATIC
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp

    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    vendor/imgui
    vendor/imgui/backends
)

target_link_libraries(imgui PUBLIC
    glfw
    glad
    OpenGL::GL
)

# Application
add_executable(ImGUI-Example
    src/main.cpp
    src/Application.cpp
    src/Application.h
)

target_link_libraries(ImGUI-Example PRIVATE
    imgui
    glad
    glfw
    OpenGL::GL
)

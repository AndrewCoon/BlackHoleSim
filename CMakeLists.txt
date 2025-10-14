cmake_minimum_required(VERSION 3.10)
project(OpenGL_Project LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# GLFW system package (Arch)
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h /usr/include)
find_library(GLFW_LIB glfw)

# Add glad.c as a static library
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Your executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# Link everything
target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    ${GLFW_LIB}
    OpenGL::GL
)


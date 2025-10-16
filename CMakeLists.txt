cmake_minimum_required(VERSION 3.15)
project(OpenGL_Project LANGUAGES C CXX)
cmake_policy(SET CMP0074 NEW)  # Enable _ROOT variable support

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# GLFW search logic
if (WIN32)
    # Use environment or manual path
    set(GLFW_ROOT $ENV{GLFW_ROOT} CACHE PATH "Path to GLFW root directory")
    if (EXISTS "${GLFW_ROOT}")
        message(STATUS "Using GLFW root: ${GLFW_ROOT}")
        find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h PATHS "${GLFW_ROOT}/include")
        find_library(GLFW_LIB NAMES glfw3 glfw PATHS "${GLFW_ROOT}/lib" "${GLFW_ROOT}/lib-mingw" "${GLFW_ROOT}/build/src/Debug")
    endif()
else()
    find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h /usr/include /usr/local/include)
    find_library(GLFW_LIB glfw)
endif()

if (NOT GLFW_INCLUDE_DIR OR NOT GLFW_LIB)
    message(FATAL_ERROR "Could not find GLFW. Please set GLFW_ROOT or install GLFW properly.")
endif()

# GLAD
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    ${GLFW_LIB}
    OpenGL::GL
)

# Platform-specific linking
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework OpenGL" "-framework IOKit")
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread X11)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

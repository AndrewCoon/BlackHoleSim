cmake_minimum_required(VERSION 3.10)
project(OpenGL_Project LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# Prefer find_package for GLFW if available, fallback otherwise
find_package(GLFW 3.3 QUIET)
if (NOT GLFW_FOUND)
    find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h /usr/include /usr/local/include)
    find_library(GLFW_LIB glfw)
else()
    set(GLFW_INCLUDE_DIR ${GLFW_INCLUDE_DIRS})
    set(GLFW_LIB ${GLFW_LIBRARIES})
endif()

# Build glad as static lib
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    ${GLFW_LIB}
    OpenGL::GL
)

# Platform-specific link libraries
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework OpenGL" "-framework IOKit")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread X11)
endif()

# Optional: specify binary output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

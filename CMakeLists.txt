cmake_minimum_required(VERSION 3.15)
project(Gravity LANGUAGES C CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# ---- Source files ----
file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# ---- Dependencies ----
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLM (header-only)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# ---- Find OpenGL ----
find_package(OpenGL REQUIRED)

# ---- Build target ----
add_executable(${PROJECT_NAME} ${SRC_FILES})

# ---- Link libraries ----
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    OpenGL::GL
)

# ---- Include directories ----
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src   # for glad.h
    ${glm_SOURCE_DIR}
)

# ---- Platform-specific fixes ----
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
elseif (UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
endif()

# Optional: warnings for good practice
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

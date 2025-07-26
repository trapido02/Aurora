cmake_minimum_required(VERSION 3.10)
project(Aurora LANGUAGES CXX)

# C++ Standard settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories by build type
set(OUTPUT_BASE "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE})

# Define sources
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp"
)

# Build the shared library
add_library(Aurora SHARED ${SRC_FILES})

# Setup the include directories
target_include_directories(Aurora PUBLIC include)
target_include_directories(Aurora PRIVATE .)

# Fetch GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)

# Require OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
target_link_libraries(Aurora PUBLIC OpenGL::GL)

# Link GLFW
target_link_libraries(Aurora PRIVATE glfw)
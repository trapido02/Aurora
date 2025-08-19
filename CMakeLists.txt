cmake_minimum_required(VERSION 3.10)
project(Aurora LANGUAGES CXX)
include(FetchContent)

# Give the user the option to choose to build shared library
option(BUILD_SHARED_LIBS "Build shared libraries (DLL)" ON)

# C++ Standard settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default symbols to hidden
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

# Set output directories by build type
set(OUTPUT_BASE "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE})

# Fetch GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Fetch tracy
FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(tracy)

# Define sources
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

# Build the library
add_library(Aurora ${SRC_FILES})
target_compile_features(Aurora PUBLIC cxx_std_23)

target_include_directories(Aurora
        PRIVATE
        # Internal implementation details
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${tracy_SOURCE_DIR}/public
        PUBLIC
        # Expose only the public API headers to consumers
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Aurora
        PUBLIC
        # For Windows builds: use __declspec
        "$<$<AND:$<BOOL:${BUILD_SHARED_LIBS}>,$<OR:$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>>>:AURORA_API=__declspec(dllexport)>"
        # For shared Unix builds on GCC or Clang: visibility("default")
        "$<$<AND:$<BOOL:${BUILD_SHARED_LIBS}>,$<OR:$<STREQUAL:${CMAKE_CXX_COMPILER_ID},GNU>,$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Clang>>>:AURORA_API=__attribute__((visibility(\"default\")))>"
        # In all other cases, it stays empty
        "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:AURORA_API=>"
)

# If building shared, define AURORA_EXPORTS so the same macro expands right during compilation
target_compile_definitions(Aurora PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:AURORA_EXPORTS>)

# Setup precompiled headers
target_precompile_headers(Aurora PRIVATE source/pch.h)

# Require OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
target_link_libraries(Aurora PUBLIC OpenGL::GL)

# Link GLFW
target_link_libraries(Aurora PRIVATE glfw)

# Enable profiler
option(TRACY_ENABLE "Enable Tracy profiling" ON)
option(TRACY_ON_DEMAND " " ON)
if(TRACY_ENABLE)
    target_compile_definitions(Aurora PRIVATE TRACY_ENABLE)
    target_compile_definitions(Aurora PRIVATE TRACY_ON_DEMAND)

    target_link_libraries(Aurora PRIVATE TracyClient)
endif()

# Enable Catch2
option(RUN_UNIT_TESTS "Build and run Catch2 tests" ON)
if (RUN_UNIT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
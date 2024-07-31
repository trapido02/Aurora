cmake_minimum_required(VERSION 3.20)
project(Aurora)

# Set the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Set properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)

# Setup library directories
target_link_directories(${PROJECT_NAME} PRIVATE vendor/glfw/lib-vc2022)

# Setup include directories
target_include_directories(${PROJECT_NAME} PRIVATE vendor/glfw/include)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	OpenGL::GL
	glfw3
)

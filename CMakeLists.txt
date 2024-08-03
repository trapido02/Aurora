cmake_minimum_required(VERSION 3.20)
project(Aurora)

# Set properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Add executables
add_executable(
	${PROJECT_NAME}
	"vendor/glad/src/glad.c"
	"source/Main.cpp"

	"source/core/Window.cpp"
	"source/core/Window.h"

	"source/core/Game.cpp"
	"source/core/Game.h"

	"source/renderer/Renderer.cpp"
	"source/renderer/Renderer.h"
)

# Setup library directories
target_link_directories(${PROJECT_NAME} PRIVATE vendor/glfw/lib-vc2022)

# Setup include directories
target_include_directories(
	${PROJECT_NAME}
	PRIVATE 
	source
	vendor/glfw/include
	vendor/glad/include
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	OpenGL::GL
	glfw3
)

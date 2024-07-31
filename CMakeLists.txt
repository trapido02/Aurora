cmake_minimum_required(VERSION 3.20)

project(Aurora)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

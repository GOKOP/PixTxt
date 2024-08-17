cmake_minimum_required(VERSION 3.20)
project(OnePixelText)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

add_library(onepixeltext ${LIB_SOURCES})
target_include_directories(onepixeltext PUBLIC "include")
set_target_properties(onepixeltext PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED 23)
target_link_libraries(onepixeltext sfml-graphics)

if(NOT MSVC)
	target_compile_options(onepixeltext PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(example "example/main.cpp")
set_target_properties(example PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED 23)
target_link_libraries(example onepixeltext)

add_custom_command(
	TARGET example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/font.png
	${CMAKE_CURRENT_BINARY_DIR}/font.png)

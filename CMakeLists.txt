cmake_minimum_required(VERSION 3.20)
project(OnePixelText VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.6 COMPONENTS graphics)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

add_library(onepixeltext ${LIB_SOURCES})
target_include_directories(onepixeltext PUBLIC "include")
set_target_properties(onepixeltext PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED 23)
set_target_properties(onepixeltext PROPERTIES VERSION ${PROJECT_VERSION})

if(NOT MSVC)
	target_compile_options(onepixeltext PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(sfml_example "examples/sfml_example.cpp")
set_target_properties(sfml_example PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED 23)
target_link_libraries(sfml_example onepixeltext sfml-graphics)

add_custom_command(
	TARGET sfml_example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/font.pbm
	${CMAKE_CURRENT_BINARY_DIR}/font.pbm)

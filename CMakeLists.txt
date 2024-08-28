cmake_minimum_required(VERSION 3.20)
project(PixTxt VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.6 COMPONENTS graphics)
find_package(PkgConfig)
pkg_check_modules(SPNG IMPORTED_TARGET spng)

file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

add_library(pixtxt ${LIB_SOURCES})
target_include_directories(pixtxt PUBLIC "include")
set_target_properties(pixtxt PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED 17)
set_target_properties(pixtxt PROPERTIES VERSION ${PROJECT_VERSION})

if(NOT MSVC)
	target_compile_options(pixtxt PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(sfml_example "examples/sfml_example.cpp")
set_target_properties(sfml_example PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED 17)
target_link_libraries(sfml_example pixtxt sfml-graphics)

add_custom_command(
	TARGET sfml_example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/font.pbm
	${CMAKE_CURRENT_BINARY_DIR}/font.pbm)

add_executable(spng_example "examples/spng_example.cpp")
set_target_properties(spng_example PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED 17)
target_link_libraries(spng_example pixtxt spng)

add_custom_command(
	TARGET spng_example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/font.pbm
	${CMAKE_CURRENT_BINARY_DIR}/font.pbm)


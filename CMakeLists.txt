cmake_minimum_required (VERSION 3.7)

project (core_utils)

add_library (core_utils SHARED)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

target_compile_options (core_utils PUBLIC
	-Wall -Wextra -Werror -pedantic
	)

set (CMAKE_VERBOSE_MAKEFILE OFF)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

# https://stackoverflow.com/questions/48428647/how-to-use-cmake-to-install
install (TARGETS core_utils LIBRARY DESTINATION lib)

# https://stackoverflow.com/questions/48212771/cmake-install-header-files-and-maintain-directory-hierarchy
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
	DESTINATION include/core_utils
	FILES_MATCHING
	PATTERN "*.hh")
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
	DESTINATION include/core_utils
	FILES_MATCHING
	PATTERN "*.hxx")

project (core_utils)

set (CMAKE_CXX_STANDARD 14)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

set (SOURCES
  CoreException.cc
  CoreLogger.cc
  CoreLoggingDevice.cc
  )

add_library (core_utils SHARED
  ${SOURCES}
  ${SDL2_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIRS}
  )

set(CORE_UTILS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_link_libraries(core_utils
  )

target_include_directories (core_utils PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )


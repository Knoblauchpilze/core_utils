
set (CMAKE_CXX_STANDARD 14)

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

set (SOURCES
  CoreException.cc
  StdLogger.cc
  PrefixedLogger.cc
  LoggerLocator.cc
  CoreObject.cc
  ThreadPool.cc
  RNG.cc
  BitReader.cc
  BitWriter.cc
  )

add_library (core_utils SHARED
  ${SOURCES}
  )

set (CORE_UTILS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_link_libraries(core_utils
  )

target_include_directories (core_utils PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )


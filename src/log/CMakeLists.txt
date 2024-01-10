
target_include_directories (core_utils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (core_utils PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Severity.cc
	${CMAKE_CURRENT_SOURCE_DIR}/StreamFormatter.cc
	${CMAKE_CURRENT_SOURCE_DIR}/StdLogger.cc
	${CMAKE_CURRENT_SOURCE_DIR}/NullLogger.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Locator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PrefixedLogger.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CoreException.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SafetyNet.cc
	)

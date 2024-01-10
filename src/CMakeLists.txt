
target_include_directories (core_utils PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/log
	)

target_sources (core_utils PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/CoreException.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SafetyNet.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CoreObject.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ThreadPool.cc
	${CMAKE_CURRENT_SOURCE_DIR}/RNG.cc
	${CMAKE_CURRENT_SOURCE_DIR}/BitReader.cc
	${CMAKE_CURRENT_SOURCE_DIR}/BitWriter.cc
	)

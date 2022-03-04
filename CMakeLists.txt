cmake_minimum_required(VERSION 3.8)

	project(Micro LANGUAGES CXX VERSION 1.0.0)

	option(BUILD_WITH_ARM_INTRINSICS "enables ARM intrinsics" OFF)
	option(BUILD_WITH_SSE_INTRINSICS "enables SSE intrinsics" OFF)
	option(BUILD_WITH_AVX_INTRINSICS "enables AVX intrinsics" OFF)

	add_library(libmath INTERFACE)

	# FEATURES
	#

	if (BUILD_WITH_AVX_INTRINSICS)
		set (BUILD_WITH_SSE_INTRINSICS ON CACHE BOOL "force SSE intrinsics" FORCE)

		if (NOT MSVC)
			# Enable AVX
			#

			target_compile_options(libmath INTERFACE "-mavx")
		endif()
	elseif (BUILD_WITH_ARM_INTRINSICS)
		if (NOT MSVC)
			# Enable NEON
			#

			target_compile_options(libmath INTERFACE "-march=armv8.1-a+simd")
		endif()
	endif(BUILD_WITH_AVX_INTRINSICS)


	message(VERBOSE "BUILD_WITH_ARM_INTRINSICS: ${BUILD_WITH_ARM_INTRINSICS}")
	message(VERBOSE "BUILD_WITH_SSE_INTRINSICS: ${BUILD_WITH_SSE_INTRINSICS}")
	message(VERBOSE "BUILD_WITH_AVX_INTRINSICS: ${BUILD_WITH_AVX_INTRINSICS}")

	target_compile_definitions(libmath INTERFACE $<$<BOOL:${BUILD_WITH_ARM_INTRINSICS}>: -DWITH_ARM_INTRINSICS>)
	target_compile_definitions(libmath INTERFACE $<$<BOOL:${BUILD_WITH_SSE_INTRINSICS}>: -DWITH_SSE_INTRINSICS>)
	target_compile_definitions(libmath INTERFACE $<$<BOOL:${BUILD_WITH_AVX_INTRINSICS}>: -DWITH_AVX_INTRINSICS>)

	target_compile_features(libmath INTERFACE cxx_std_17)

	# INCLUDE
	#

	target_include_directories(libmath INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

	# INSTALLATION
	#

	include(GNUInstallDirs)

	install(FILES "${PROJECT_SOURCE_DIR}/include/libmath/matrix.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x2.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x2_arm.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x2_sse.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x3.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x4.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2xN_transform.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x2.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x3.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x3_arm.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x3_sse.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x4.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3xN_transform.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x2.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x3.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x4.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x4_arm.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x4_sse.inl     "
		      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4xN_transform.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector2.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector2_arm.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector2_sse.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector3.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector3_arm.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector3_sse.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector4.hh"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector4_arm.inl"
		      "${PROJECT_SOURCE_DIR}/include/libmath/vector4_sse.inl" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libmath COMPONENT dev)

	target_include_directories(libmath INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

	# TESTING
	#

	include(CTest)

	if(BUILD_TESTING)
		add_executable(libmath-test-vector2 test/vector2.cc)
		add_executable(libmath-test-vector3 test/vector3.cc)
		add_executable(libmath-test-vector4 test/vector4.cc)
		add_executable(libmath-test-matrix2 test/matrix2.cc)
		add_executable(libmath-test-matrix3 test/matrix3.cc)
		add_executable(libmath-test-matrix4 test/matrix4.cc)

		add_test(NAME vector2 COMMAND $<TARGET_FILE:libmath-test-vector2>)
		add_test(NAME vector3 COMMAND $<TARGET_FILE:libmath-test-vector3>)
		add_test(NAME vector4 COMMAND $<TARGET_FILE:libmath-test-vector4>)
		add_test(NAME matrix2 COMMAND $<TARGET_FILE:libmath-test-matrix2>)
		add_test(NAME matrix3 COMMAND $<TARGET_FILE:libmath-test-matrix3>)
		add_test(NAME matrix4 COMMAND $<TARGET_FILE:libmath-test-matrix4>)

		target_link_libraries(libmath-test-vector2 PRIVATE libmath)
		target_link_libraries(libmath-test-vector3 PRIVATE libmath)
		target_link_libraries(libmath-test-vector4 PRIVATE libmath)
		target_link_libraries(libmath-test-matrix2 PRIVATE libmath)
		target_link_libraries(libmath-test-matrix3 PRIVATE libmath)
		target_link_libraries(libmath-test-matrix4 PRIVATE libmath)
	endif()
	
	# ALIAS
	#
	
	add_library(${PROJECT_NAME}::math ALIAS libmath)

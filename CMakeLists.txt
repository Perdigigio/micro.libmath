cmake_minimum_required(VERSION 3.8)

        project(Micro_Libmath LANGUAGES CXX VERSION 1.0.0)
                add_library(micro.libmath INTERFACE)

        #
        # FEATURES
        #

        target_compile_features(micro.libmath INTERFACE cxx_std_17)

        #
        # INSTALLATION
        #

        include(GNUInstallDirs)

        install(FILES "${PROJECT_SOURCE_DIR}/matrix.hh"
                      "${PROJECT_SOURCE_DIR}/matrix2x2.hh"
                      "${PROJECT_SOURCE_DIR}/matrix2x2_arm.inl"
                      "${PROJECT_SOURCE_DIR}/matrix2x2_sse.inl"
                      "${PROJECT_SOURCE_DIR}/matrix2x3.hh"
                      "${PROJECT_SOURCE_DIR}/matrix2x4.hh"
                      "${PROJECT_SOURCE_DIR}/matrix2xN_transform.hh"
                      "${PROJECT_SOURCE_DIR}/matrix3x2.hh"
                      "${PROJECT_SOURCE_DIR}/matrix3x3.hh"
                      "${PROJECT_SOURCE_DIR}/matrix3x3_arm.inl"
                      "${PROJECT_SOURCE_DIR}/matrix3x3_sse.inl"
                      "${PROJECT_SOURCE_DIR}/matrix3x4.hh"
                      "${PROJECT_SOURCE_DIR}/matrix3xN_transform.hh"
                      "${PROJECT_SOURCE_DIR}/matrix4x2.hh"
                      "${PROJECT_SOURCE_DIR}/matrix4x3.hh"
                      "${PROJECT_SOURCE_DIR}/matrix4x4.hh"
                      "${PROJECT_SOURCE_DIR}/matrix4x4_arm.inl"
                      "${PROJECT_SOURCE_DIR}/matrix4x4_sse.inl     "
                      "${PROJECT_SOURCE_DIR}/matrix4xN_transform.hh"
                      "${PROJECT_SOURCE_DIR}/vector.hh"
                      "${PROJECT_SOURCE_DIR}/vector2.hh"
                      "${PROJECT_SOURCE_DIR}/vector2_arm.inl"
                      "${PROJECT_SOURCE_DIR}/vector2_sse.inl"
                      "${PROJECT_SOURCE_DIR}/vector3.hh"
                      "${PROJECT_SOURCE_DIR}/vector3_arm.inl"
                      "${PROJECT_SOURCE_DIR}/vector3_sse.inl"
                      "${PROJECT_SOURCE_DIR}/vector4.hh"
                      "${PROJECT_SOURCE_DIR}/vector4_arm.inl"
                      "${PROJECT_SOURCE_DIR}/vector4_sse.inl" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libmath COMPONENT dev)

        #
        # TESTING
        #

        include(CTest)

        if(BUILD_TESTING)
                add_executable(libmath-test-matrix2xN test/matrix2xN.cc)
                add_executable(libmath-test-matrix3xN test/matrix3xN.cc)
                add_executable(libmath-test-matrix4xN test/matrix4xN.cc)

                add_test(NAME matrix2xN COMMAND $<TARGET_FILE:libmath-test-matrix2xN>)
                add_test(NAME matrix3xN COMMAND $<TARGET_FILE:libmath-test-matrix3xN>)
                add_test(NAME matrix4xN COMMAND $<TARGET_FILE:libmath-test-matrix4xN>)

                target_include_directories(libmath-test-matrix2xN PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-matrix3xN PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-matrix4xN PRIVATE ${PROJECT_SOURCE_DIR})

                target_link_libraries(libmath-test-matrix2xN PRIVATE micro.libmath)
                target_link_libraries(libmath-test-matrix3xN PRIVATE micro.libmath)
                target_link_libraries(libmath-test-matrix4xN PRIVATE micro.libmath)
        endif()

cmake_minimum_required(VERSION 3.8)

        project(Micro LANGUAGES CXX VERSION 1.0.0)
                add_library(libmath INTERFACE)

        # FEATURES
        #

        target_compile_features(libmath INTERFACE cxx_std_17)

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

                target_include_directories(libmath-test-vector2 PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-vector3 PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-vector4 PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-matrix2 PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-matrix3 PRIVATE ${PROJECT_SOURCE_DIR})
                target_include_directories(libmath-test-matrix4 PRIVATE ${PROJECT_SOURCE_DIR})

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

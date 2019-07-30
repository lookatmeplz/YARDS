cmake_minimum_required(VERSION 3.4)
project(YARDS)

set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(config/google-test.cmake googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# Add Sub Directory (Source Files)
add_subdirectory(src)

# Now simply link against gtest or gtest_main as needed. Eg

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

if(TEST_SRC_FILES)
    add_executable(test_unit ${TEST_SRC_FILES})
    target_link_libraries(
            test_unit
            gtest
            gtest_main
            atomic
            data_pack
            struct
            net_server
            net_client
            cmd
    )
    add_test(UnitTests test_unit)
endif()

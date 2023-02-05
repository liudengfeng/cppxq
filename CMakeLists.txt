cmake_minimum_required(VERSION 3.24)
project(muzeroxq)

option(MUZERO_TEST "Enable testing" OFF)

# ##############################################################################
# Global compiler config
set(CMAKE_CXX_STANDARD 17)
set(PYBIND11_CPP_STANDARD -std=c++17)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wno-register -Wno-deprecated-declarations -fPIC -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 7.1
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.1)
        message(FATAL_ERROR "GCC version must be at least 7.1!")
    endif()
endif()

find_package(Threads)
find_package(Python COMPONENTS Interpreter Development)
find_package(fmt)
find_package(GTest)
find_package(pybind11)

set(XQ_SOURCES
    src/common.cpp
    src/board.cpp
    src/board_utils.cpp
    src/rule2022.cpp
    src/xqboard.cpp
    src/Pybind.cpp
)

add_library(muzeroxq ${XQ_SOURCES})

# Include everything in src
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(muzeroxq PRIVATE
    pybind11::lto pybind11::embed pybind11::module
    $<BUILD_INTERFACE:${PYTHON_LIBRARIES}>
    fmt::fmt-header-only
)

pybind11_add_module(xqcpp src/pybind_module.cpp)
target_link_libraries(xqcpp PRIVATE
    muzeroxq
)

target_link_libraries(xqcpp PRIVATE
    pybind11::lto pybind11::embed pybind11::module
    $<BUILD_INTERFACE:${PYTHON_LIBRARIES}>
    fmt::fmt-header-only
)

if (MUZERO_TEST)
    enable_testing()
    include(GoogleTest)
    
    # Define a convenience function for tests
    function(add_cpp_tests prefix lib_to_link)
        set(test_list ${ARGV})
        list(REMOVE_AT test_list 0)
        list(REMOVE_AT test_list 0)
    
        foreach(test_file ${test_list})
            string(REPLACE "/" "_" test_name ${test_file})
            string(REPLACE "test_" "" test_name ${test_name})
            string(REPLACE ".cpp" "" test_name ${test_name})
            string(CONCAT test_name ${prefix} ${test_name})
            add_executable(${test_name} ${test_file})
    
            add_test(${test_name} ${test_name})
            target_link_libraries(${test_name} ${lib_to_link} GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main fmt::fmt-header-only)
        endforeach(test_file)
    endfunction(add_cpp_tests)
    
    set(XQ_TEST_SOURCES
        src/test_common.cpp
        src/test_utils.cpp
        src/test_board_basic.cpp
        src/test_board.cpp
        src/test_board_utils.cpp
        src/test_node.cpp
    
        src/test_rule_utils.cpp
        src/test_rule_sha.cpp
        src/test_rule_chi.cpp
        src/test_rule_jdz.cpp
    
        src/test_mark_utils.cpp
        src/test_mark_2022.cpp
        src/test_mark_2022_plus.cpp
    
        src/test_xboard.cpp
        src/test_temp.cpp
    )
    
    add_cpp_tests(test_ muzeroxq ${XQ_TEST_SOURCES})
endif()

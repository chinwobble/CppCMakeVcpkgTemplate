# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(cpp_template)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT APPLE)
    # set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()
add_compile_options(-march=haswell -maes)


# Find dependencies provided by vcpkg (via vcpkg.cmake)
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE
    CPP_TEMPLATE_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE
    CPP_TEMPLATE_TEST_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
)

# main target
add_executable(main ${CPP_TEMPLATE_SOURCES})
target_precompile_headers(main
  PRIVATE
    <string>
    <fmt/core.h>
    <array>
    <immintrin.h>
)
target_link_libraries(main PRIVATE fmt::fmt-header-only)
set_property(TARGET main PROPERTY CXX_STANDARD 23)

# tests target
enable_testing()
# if (BUILD_TESTING)
foreach (TESTFILE IN LISTS CPP_TEMPLATE_TEST_SOURCES)

    get_filename_component(TESTNAME ${TESTFILE} NAME_WE)
    add_executable(${TESTNAME} ${TESTFILE})
    set_property(TARGET ${TESTNAME} PROPERTY CXX_STANDARD 23)
    target_link_libraries(${TESTNAME} PRIVATE fmt::fmt-header-only
        GTest::gtest
        GTest::gtest_main)
    set_property(TARGET ${TESTNAME} PROPERTY CXX_STANDARD 23)
    add_test(${TESTNAME} ${TESTNAME})

    target_precompile_headers(${TESTNAME}
    PRIVATE
        <string>
        <fmt/core.h>
        <gtest/gtest.h>
        <array>
        <immintrin.h>
    )
endforeach()
# endif()

# add_test(tests tests)


add_custom_target(
    check-format
    COMMAND clang-format --dry-run ${CPP_TEMPLATE_SOURCES} ${CPP_TEMPLATE_TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)

add_custom_target(
    format
    COMMAND clang-format -i ${CPP_TEMPLATE_SOURCES} ${CPP_TEMPLATE_TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)
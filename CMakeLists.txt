# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(cpp_template)
## HWY_AVX2 which is 256
# SET(GCC_COVERAGE_COMPILE_FLAGS "-march=haswell -maes")
## HWY_AVX3 which is 512
# SET(GCC_COVERAGE_COMPILE_FLAGS "-march=sapphirerapids")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
# Find dependencies provided by vcpkg (via vcpkg.cmake)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(hwy CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)
if (MSVC)
    add_compile_options(/arch:AVX2 /Gv)
endif()

# main target
add_executable(bench)
target_sources(
    bench PRIVATE
    benchmarks/bench.cpp
    src/read.cpp
    src/sequence.cpp
)
target_link_libraries(bench PRIVATE hwy::hwy benchmark::benchmark benchmark::benchmark_main)
set_property(TARGET bench PROPERTY CXX_STANDARD 23)

# main target
add_executable(main)
target_sources(main PRIVATE src/main.cpp)
target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3 fmt::fmt-header-only hwy::hwy)
set_property(TARGET main PROPERTY CXX_STANDARD 23)

# tests target
add_executable(tests)
target_sources(tests PRIVATE src/test.cpp)
target_link_libraries(tests PRIVATE unofficial::sqlite3::sqlite3 fmt::fmt-header-only)
set_property(TARGET tests PROPERTY CXX_STANDARD 23)
enable_testing()
add_test(tests tests)
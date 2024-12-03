# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(cpp_template)
## HWY_AVX2 which is 256
# SET(GCC_COVERAGE_COMPILE_FLAGS "-march=haswell -maes")
## HWY_AVX3 which is 512
# SET(GCC_COVERAGE_COMPILE_FLAGS "-march=sapphirerapids")
# add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
# Find dependencies provided by vcpkg (via vcpkg.cmake)
find_package(fmt CONFIG REQUIRED)
find_package(hwy CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)
if (MSVC)
    add_compile_options(/arch:AVX2 /Gv)
endif()

find_package(libdeflate CONFIG REQUIRED)

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
target_sources(
    main PRIVATE
    src/common.h
    src/fastareader.cpp
    src/fastareader.h
    src/main.cpp
    src/options.h
    src/options.cpp
    src/read.cpp
    src/read.h
    src/readpool.cpp
    src/readpool.h
    src/sequence.cpp
    src/sequence.h
    src/singleproducersingleconsumerlist.h
    src/util.h
    src/writer.cpp
    src/writer.h
)
target_link_libraries(
    main PRIVATE
    fmt::fmt-header-only
    hwy::hwy
    $<IF:$<TARGET_EXISTS:libdeflate::libdeflate_shared>,libdeflate::libdeflate_shared,libdeflate::libdeflate_static>
)
target_link_options(
    main
    PRIVATE
    -lpthread
)
set_property(TARGET main PROPERTY CXX_STANDARD 23)
# tests target
add_executable(tests)
target_sources(tests PRIVATE src/test.cpp)
target_link_libraries(tests PRIVATE fmt::fmt-header-only)
set_property(TARGET tests PROPERTY CXX_STANDARD 23)
enable_testing()
add_test(tests tests)
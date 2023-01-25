include(FetchContent)

FetchContent_Declare(
    gtest
    QUIET
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

FetchContent_Declare(
    gbenchmark
    QUIET
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.6.0
)

FetchContent_Declare(
    snapshot
    QUIET
    GIT_REPOSITORY https://github.com/Dup4/snapshot-cpp.git
    GIT_TAG v0.1.11
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest gbenchmark snapshot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DORMXX_BUILD_TESTS")

file(GLOB UNITTEST_FILE
    "ormxx/*_test.cc"
    "ormxx/adaptor/mysql/*_test.cc"
    "ormxx/internal/*_test.cc"
    "ormxx/interface/*_test.cc"
    "ormxx/type_traits/*_test.cc"
    "ormxx/types_check/*_test.cc"
)
add_executable(
    unit_test
    ${UNITTEST_FILE}
)

target_link_libraries(
    unit_test
PRIVATE
    snapshot
    fmt::fmt
    mysqlcppconn
    gtest
    gtest_main
)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(
    unit_test
PROPERTIES
    LABELS "unit"
DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)

file(GLOB BENCHMARK_FILE
    "ormxx/*_benchmark.cc"
)
add_executable(
    unit_benchmark
    ${BENCHMARK_FILE}
)

target_link_libraries(
    unit_benchmark
PRIVATE
    snapshot
    gtest
    fmt::fmt
    mysqlcppconn
    benchmark::benchmark
    benchmark::benchmark_main
)

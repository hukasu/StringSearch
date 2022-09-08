cmake_minimum_required(VERSION 3.9.0)

project("StringSearch")

option("BUILD_TESTS" "Enables building of tests" OFF)

add_library(
    string_search
    STATIC
    src/naive.cpp
    src/kmp.cpp
)
target_include_directories(
    string_search
    INTERFACE src/
)
target_compile_features(
    string_search
    PUBLIC cxx_std_20
)

if (BUILD_TESTS)
    enable_testing()

    find_package("doctest" CONFIG REQUIRED)

    add_executable(
        kmp_tests
        test/kmp_tests.cpp
    )
    target_link_libraries(
        kmp_tests
        PUBLIC string_search
        PRIVATE doctest::doctest
    )
    target_compile_features(
        string_search
        PUBLIC cxx_std_20
    )
    add_test(
        NAME kmp_test
        COMMAND "kmp_tests"
    )

    add_executable(
        naive_tests
        test/naive_tests.cpp
    )
    target_link_libraries(
        naive_tests
        PUBLIC string_search
        PRIVATE doctest::doctest
    )
    target_compile_features(
        naive_tests
        PUBLIC cxx_std_20
    )
    add_test(
        NAME naive_test
        COMMAND "naive_tests"
    )
endif(BUILD_TESTS)
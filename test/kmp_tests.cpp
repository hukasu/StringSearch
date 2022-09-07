/**
 * @file kmp_tests.cpp
 * @author your name (you@domain.com)
 * @brief Tests for Knuth–Morris–Pratt algorithm
 * @version 0.1
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <sstream>

#include "kmp.hpp"

TEST_CASE("Table Build 1") {
    std::unique_ptr<std::stringstream> search = std::make_unique<std::stringstream>(
        "",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> word = std::make_unique<std::stringstream>(
        "ABCDABD",
        std::ios::in | std::ios::binary
    );

    string_search::KMP kmp(std::move(search), std::move(word));
    
    const std::vector<int64_t>& built_table = kmp.getTable();
    const std::vector<int64_t> test_table = {-1, 0, 0, 0, -1, 0, 2, 0};

    CHECK_EQ(built_table, test_table);
}

TEST_CASE("Table Build 2") {
    std::unique_ptr<std::stringstream> search = std::make_unique<std::stringstream>(
        "",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> word = std::make_unique<std::stringstream>(
        "ABACABABC",
        std::ios::in | std::ios::binary
    );

    string_search::KMP kmp(std::move(search), std::move(word));
    
    const std::vector<int64_t>& built_table = kmp.getTable();
    const std::vector<int64_t> test_table = {-1, 0, -1, 1, -1, 0, -1, 3, 2, 0};

    CHECK_EQ(built_table, test_table);
}

TEST_CASE("Table Build 3") {
    std::unique_ptr<std::stringstream> search = std::make_unique<std::stringstream>(
        "",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> word = std::make_unique<std::stringstream>(
        "ABACABABA",
        std::ios::in | std::ios::binary
    );

    string_search::KMP kmp(std::move(search), std::move(word));
    
    const std::vector<int64_t>& built_table = kmp.getTable();
    const std::vector<int64_t> test_table = {-1, 0, -1, 1, -1, 0, -1, 3, -1, 3};

    CHECK_EQ(built_table, test_table);
}

TEST_CASE("Table Build 4") {
    std::unique_ptr<std::stringstream> search = std::make_unique<std::stringstream>(
        "",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> word = std::make_unique<std::stringstream>(
        "PARTICIPATE IN PARACHUTE",
        std::ios::in | std::ios::binary
    );

    string_search::KMP kmp(std::move(search), std::move(word));
    
    const std::vector<int64_t>& built_table = kmp.getTable();
    const std::vector<int64_t> test_table = {
        -1, 0, 0, 0, 0, 0, 0, -1,
        0, 2, 0, 0, 0, 0, 0, -1,
        0, 0, 3, 0, 0, 0, 0, 0, 0
    };

    CHECK_EQ(built_table, test_table);
}

TEST_CASE("String search test 1") {
    std::unique_ptr<std::stringstream> search = std::make_unique<std::stringstream>(
        "ABC ABCDAB ABCDABCDABDE",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> word = std::make_unique<std::stringstream>(
        "ABCDABD",
        std::ios::in | std::ios::binary
    );

    string_search::KMP kmp(std::move(search), std::move(word));
    
    std::optional<size_t> result = kmp.next();

    if (result.has_value()) CHECK_EQ(result.value(), 15);
    else FAIL(1);
}

TEST_CASE("String search test 2") {
    std::unique_ptr<std::stringstream> search = std::make_unique<std::stringstream>(
        "TETTE TERETTE",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> word = std::make_unique<std::stringstream>(
        "TE",
        std::ios::in | std::ios::binary
    );

    string_search::KMP kmp(std::move(search), std::move(word));
    
    std::optional<size_t> result = kmp.next();
    if (result.has_value()) CHECK_EQ(result.value(), 0);
    else FAIL(1);

    result = kmp.next();
    if (result.has_value()) CHECK_EQ(result.value(), 3);
    else FAIL(1);

    result = kmp.next();
    if (result.has_value()) CHECK_EQ(result.value(), 6);
    else FAIL(1);

    result = kmp.next();
    if (result.has_value()) CHECK_EQ(result.value(), 11);
    else FAIL(1);
}
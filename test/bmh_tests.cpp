/**
 * @file naive_tests.cpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Tests for Naive string search
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <sstream>

#include "bmh.hpp"

TEST_CASE("String search test 1") {
    std::unique_ptr<std::stringstream> text = std::make_unique<std::stringstream>(
        "ABC ABCDAB ABCDABCDABDE",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> pattern = std::make_unique<std::stringstream>(
        "ABCDABD",
        std::ios::in | std::ios::binary
    );

    string_search::BoyerMooreHorspoolStringSearch bmh(std::move(text), std::move(pattern));
    
    std::optional<size_t> result = bmh.next();

    if (result.has_value()) CHECK_EQ(result.value(), 15);
    else FAIL(1);
}

TEST_CASE("String search test 2") {
    std::unique_ptr<std::stringstream> text = std::make_unique<std::stringstream>(
        "TETTE TERETTE",
        std::ios::in | std::ios::binary
    );
    std::unique_ptr<std::stringstream> pattern = std::make_unique<std::stringstream>(
        "TE",
        std::ios::in | std::ios::binary
    );

    string_search::BoyerMooreHorspoolStringSearch bmh(std::move(text), std::move(pattern));
    
    std::optional<size_t> result = bmh.next();
    if (result.has_value()) CHECK_EQ(result.value(), 0);
    else FAIL(1);

    result = bmh.next();
    if (result.has_value()) CHECK_EQ(result.value(), 3);
    else FAIL(1);

    result = bmh.next();
    if (result.has_value()) CHECK_EQ(result.value(), 6);
    else FAIL(1);

    result = bmh.next();
    if (result.has_value()) CHECK_EQ(result.value(), 11);
    else FAIL(1);
}
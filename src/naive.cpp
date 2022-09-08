/**
 * @file naive.cpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of naive string search
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "naive.hpp"

namespace string_search {
    NaiveStringSearch::NaiveStringSearch(
        std::unique_ptr<std::istream> search,
        std::unique_ptr<std::istream> word
    ) : BaseStringSearch(std::move(search), std::move(word)) {}

    std::optional<size_t> NaiveStringSearch::next() {
        typename std::istream::pos_type s_rewind;
        typename std::istream::char_type s_c, w_c;
        bool is_comparing = false;

        while (text->good() && pattern->good()) {
            text->get(s_c);
            pattern->get(w_c);

            if (is_comparing && (s_c == w_c)) {
                continue;
            } else if (is_comparing && (s_c != w_c)) {
                if (pattern->eof()) break;
                is_comparing = false;

                text->seekg(s_rewind, std::ios::beg);
                pattern->seekg(0, std::ios::beg);
            } else if (!is_comparing && (s_c == w_c)) {
                is_comparing = true;

                s_rewind = text->tellg();
            } else if (!is_comparing && (s_c != w_c)) {
                pattern->unget();
            }
        }

        if (pattern->eof()) {
            pattern->clear();
            pattern->seekg(0, std::ios::beg);
            text->seekg(s_rewind, std::ios::beg);

            return std::optional<size_t>(static_cast<size_t>(s_rewind) - 1);
        } else if (text->eof()) {
            return std::optional<size_t>();
        } else {
            throw std::runtime_error("An error occured while running the string search.");
        }
    }
}
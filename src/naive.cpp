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

        while (search->good() && word->good()) {
            search->get(s_c);
            word->get(w_c);

            if (is_comparing && (s_c == w_c)) {
                continue;
            } else if (is_comparing && (s_c != w_c)) {
                if (word->eof()) break;
                is_comparing = false;

                search->seekg(s_rewind, std::ios::beg);
                word->seekg(0, std::ios::beg);
            } else if (!is_comparing && (s_c == w_c)) {
                is_comparing = true;

                s_rewind = search->tellg();
            } else if (!is_comparing && (s_c != w_c)) {
                word->unget();
            }
        }

        if (word->eof()) {
            word->clear();
            word->seekg(0, std::ios::beg);
            search->seekg(s_rewind, std::ios::beg);

            return std::optional<size_t>(static_cast<size_t>(s_rewind) - 1);
        } else if (search->eof()) {
            return std::optional<size_t>();
        } else {
            throw std::runtime_error("An error occured while running the string search.");
        }
    }
}
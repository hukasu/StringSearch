/**
 * @file kmp.cpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of Knuth–Morris–Pratt algorithm
 * @version 0.1
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "kmp.hpp"

namespace string_search {
    KnuthMorrisPrattStringSearch::KnuthMorrisPrattStringSearch(
        std::unique_ptr<std::istream> search,
        std::unique_ptr<std::istream> word
    ) : BaseStringSearch(std::move(search), std::move(word)) {
        buildTable();
    }

    void KnuthMorrisPrattStringSearch::buildTable() {
        typename std::istream::pos_type pos = 1, cur = 0;
        typename std::istream::char_type pos_c, cur_c;
        
        // Get word size
        pattern->seekg(0, std::ios::end);
        const typename std::istream::pos_type word_end = pattern->tellg();
        // Reserve table
        table.resize(static_cast<size_t>(word_end) + 1, 0);
        // Reset word
        pattern->seekg(0, std::ios::beg);

        // Initial table value
        table[0] = -1;

        pattern = seekAndPeek(std::move(pattern), cur, cur_c);
        pattern = seekAndPeek(std::move(pattern), pos, pos_c);
        for (pos = 1; pos < word_end; ) {
            if (pos_c == cur_c) {
                table[pos] = table[cur]; 
            } else {
                table[pos] = cur;
                while (cur >= 0 && pos_c != cur_c) {
                    cur = table[cur];
                    if (cur >= 0) {
                        pattern = seekAndPeek(std::move(pattern), cur, cur_c);
                    }
                }
            }

            pos += 1;
            pattern = seekAndPeek(std::move(pattern), pos, pos_c);
            cur += 1;
            pattern = seekAndPeek(std::move(pattern), cur, cur_c);
        }

        table[pos] = cur;
        pattern->seekg(std::ios::beg, 0);
    }

    std::optional<size_t> KnuthMorrisPrattStringSearch::next() {
        typename std::istream::char_type s_c, w_c;

        // Get current character
        s_c = text->peek();
        w_c = pattern->peek();
        while (text->good() && pattern->good()) {
            if (w_c == s_c) {
                // Advance pointers by one
                text->ignore();
                pattern->ignore();
            } else {
                typename std::istream::pos_type w_pos = table[static_cast<int64_t>(pattern->tellg())];
                if (w_pos < 0) {
                    text->ignore();
                    pattern->seekg(0, std::ios::beg);
                } else {
                    pattern->seekg(w_pos, std::ios::beg);
                }
            }

            // Get current character
            s_c = text->peek();
            w_c = pattern->peek();
        }

        if (pattern->eof()) {
            // Reset EOF
            text->clear();
            pattern->clear();

            // Calculate start of match
            typename std::istream::pos_type s_pos = text->tellg();
            typename std::istream::pos_type w_pos = pattern->tellg();
            typename std::istream::pos_type r_pos = s_pos - w_pos;

            pattern->seekg(table[w_pos] + 1, std::ios::beg);

            return std::optional<size_t>(r_pos);
        } else if (text->eof()) {
            return std::optional<size_t>();
        } else {
            throw std::runtime_error("An error occured while running the string search.");
        }
    }

    std::unique_ptr<std::istream> KnuthMorrisPrattStringSearch::seekAndPeek(
        std::unique_ptr<std::istream> stream,
        std::istream::pos_type pos,
        std::istream::char_type &var
    ) {
        std::istream::pos_type prev_pos = stream->tellg();
        
        stream->seekg(pos);
        var = stream->peek();

        stream->seekg(prev_pos);

        return std::move(stream);
    }

    const std::vector<int64_t>& KnuthMorrisPrattStringSearch::getTable() const {
        return table;
    }
}
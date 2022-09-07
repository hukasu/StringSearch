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
    KMP::KMP(
        std::unique_ptr<std::istream> search,
        std::unique_ptr<std::istream> word
    ) {
        this->search = std::move(search);
        this->word = std::move(word);
        buildTable();
    }

    void KMP::buildTable() {
        typename std::istream::pos_type pos = 1, cur = 0;
        typename std::istream::char_type pos_c, cur_c;
        
        // Get word size
        word->seekg(0, std::ios::end);
        const typename std::istream::pos_type word_end = word->tellg();
        // Reserve table
        table.resize(static_cast<size_t>(word_end) + 1, 0);
        // Reset word
        word->seekg(0, std::ios::beg);

        // Initial table value
        table[0] = -1;

        word = seekAndPeek(std::move(word), cur, cur_c);
        word = seekAndPeek(std::move(word), pos, pos_c);
        for (pos = 1; pos < word_end; ) {
            if (pos_c == cur_c) {
                table[pos] = table[cur]; 
            } else {
                table[pos] = cur;
                while (cur >= 0 && pos_c != cur_c) {
                    cur = table[cur];
                    if (cur >= 0) {
                        word = seekAndPeek(std::move(word), cur, cur_c);
                    }
                }
            }

            pos += 1;
            word = seekAndPeek(std::move(word), pos, pos_c);
            cur += 1;
            word = seekAndPeek(std::move(word), cur, cur_c);
        }

        table[pos] = cur;
        word->seekg(std::ios::beg, 0);
    }

    std::optional<size_t> KMP::next() {
        typename std::istream::char_type s_c, w_c;

        // Get current character
        s_c = search->peek();
        w_c = word->peek();
        while (search->good() && word->good()) {
            if (w_c == s_c) {
                // Advance pointers by one
                search->ignore();
                word->ignore();
            } else {
                typename std::istream::pos_type w_pos = table[static_cast<int64_t>(word->tellg())];
                if (w_pos < 0) {
                    search->ignore();
                    word->seekg(0, std::ios::beg);
                } else {
                    word->seekg(w_pos, std::ios::beg);
                }
            }

            // Get current character
            s_c = search->peek();
            w_c = word->peek();
        }

        if (word->eof()) {
            // Reset EOF
            search->clear();
            word->clear();

            // Calculate start of match
            typename std::istream::pos_type s_pos = search->tellg();
            typename std::istream::pos_type w_pos = word->tellg();
            typename std::istream::pos_type r_pos = s_pos - w_pos;

            word->seekg(table[w_pos] + 1, std::ios::beg);

            return std::optional<size_t>(r_pos);
        } else if (search->eof()) {
            return std::optional<size_t>();
        } else {
            throw std::runtime_error("An error occured while running the string search.");
        }
    }

    std::unique_ptr<std::istream> KMP::seekAndPeek(
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

    const std::vector<int64_t>& KMP::getTable() const {
        return table;
    }
}
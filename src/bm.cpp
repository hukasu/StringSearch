/**
 * @file bm.cpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of Boyer-Moore algorithm
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "bm.hpp"

namespace string_search {
    BoyerMooreStringSearch::BoyerMooreStringSearch(
        std::unique_ptr<std::istream> text,
        std::unique_ptr<std::istream> pattern
    ) : BaseStringSearch(std::move(text), std::move(pattern)) {
        makeBadCharTable();
        makeGoodPrefixTable();
    }

    typename std::istream::pos_type BoyerMooreStringSearch::getStreamLenght(
        std::unique_ptr<std::istream> &stream
    ) {
        typename std::istream::pos_type len, rewind;
        rewind = stream->tellg();
        stream->seekg(0, std::ios::end);
        len = stream->tellg();
        stream->seekg(rewind, std::ios::beg);
        return len;
    }

    void BoyerMooreStringSearch::makeBadCharTable() {
        pattern->seekg(0, std::ios::beg);
        typename std::istream::pos_type pat_len = getStreamLenght(pattern);
        
        bad_char.resize(
            1 + std::numeric_limits<typename std::istream::char_type>::max() - std::numeric_limits<typename std::istream::char_type>::min(),
            pat_len
        );

        while (pattern->good()) {
            uint8_t c = pattern->get();
            
            if (pattern->eof()) break;

            bad_char[c] = pat_len - pattern->tellg();
        }

        pattern->clear();
        pattern->seekg(0, std::ios::beg);
    }

    void BoyerMooreStringSearch::makeGoodPrefixTable() {
        auto isPrefix = [=] (size_t pattern_len, size_t pos) -> bool {
            size_t suffix_len = pattern_len - pos;
            typename std::istream::pos_type rewind = pattern->tellg();

            for (size_t i = 0; i < suffix_len; i++) {
                if (pattern->seekg(i, std::ios::beg).peek() != pattern->seekg(pos, std::ios::cur).peek()) {
                    pattern->seekg(rewind, std::ios::beg);
                    return false;
                }
            }

            pattern->seekg(rewind, std::ios::beg);
            return true;
        };

        auto suffixLength = [=] (size_t pattern_len, size_t pos) -> size_t {
            size_t i;
            for (i = 0; i <= pos; i++)
                if (
                    pattern->seekg(
                        pos - i, std::ios::beg
                    ).peek() != pattern->seekg(
                        pattern_len - 1 - i, std::ios::beg
                    ).peek()
                ) break;
            return i;
        };

        pattern->seekg(0, std::ios::beg);
        size_t pat_len = getStreamLenght(pattern);
        size_t last_prefix = 1;

        good_preffix.resize(pat_len);

        for (size_t p = pat_len; p > 0; p--) {
            if (isPrefix(pat_len, p)) {
                last_prefix = p;
            }
            good_preffix[p - 1] = last_prefix + (pat_len - p);
        }

        for (size_t p = 0; p < pat_len - 1; p++) {
            size_t suffix_len = suffixLength(pat_len, p);
            if (
                pattern->seekg(
                    p - suffix_len, std::ios::beg
                ).peek() != pattern->seekg(
                    pat_len - 1 - suffix_len, std::ios::beg
                ).peek()
            ) good_preffix[pat_len - 1 - suffix_len] = pat_len - 1 - p + suffix_len;
        }

        pattern->clear();
        pattern->seekg(0, std::ios::beg);
    }

    std::optional<size_t> BoyerMooreStringSearch::next() {
        size_t text_len = getStreamLenght(text);
        size_t pat_len = getStreamLenght(pattern);
        
        text->seekg(pat_len - 1, std::ios::cur);
        while (text->good()) {
            pattern->seekg(pat_len - 1);
            while (pattern->tellg() != 0 && (text->peek() == pattern->peek())) {
                text->seekg(-1, std::ios::cur);
                pattern->seekg(-1, std::ios::cur);
            }
            if (pattern->tellg() == 0) {
                if (text->peek() == pattern->peek()) {
                    typename std::istream::pos_type res = text->tellg();
                    text->seekg(1, std::ios::cur);
                    return std::optional<size_t>(res);
                }
            }

            text->seekg(std::max(bad_char[text->peek()], good_preffix[pattern->tellg()]), std::ios::cur);
        }

        if (text->eof()) {
            return std::optional<size_t>();
        } else {
            throw std::runtime_error("An error occured while running the string search.");
        }
    }
}
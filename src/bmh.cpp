/**
 * @file bmh.cpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of Boyer-Moore-Horspool algorithm
 * @version 0.1
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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

#include "bmh.hpp"

namespace string_search {
    BoyerMooreHorspoolStringSearch::BoyerMooreHorspoolStringSearch(
        std::unique_ptr<std::istream> text,
        std::unique_ptr<std::istream> pattern
    ) : BaseStringSearch(std::move(text), std::move(pattern)) {
        makeBadCharTable();
    }

    void BoyerMooreHorspoolStringSearch::makeBadCharTable() {
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

    bool BoyerMooreHorspoolStringSearch::same(size_t pattern_length) {
        typename std::istream::pos_type t_rewind, p_rewind;
        t_rewind = text->tellg();
        p_rewind = pattern->tellg();

        auto rewinder = [=] () {
            text->seekg(t_rewind);
            pattern->seekg(p_rewind);   
        };

        // Check tail
        text->seekg(pattern_length - 1, std::ios::cur);
        pattern->seekg(pattern_length - 1, std::ios::cur);

        // Get tail character and rewind
        typename std::istream::char_type t_c = text->peek(), p_c = pattern->peek();
        rewinder();

        if (t_c != p_c) return false;

        // Full check
        bool result = true;
        for (size_t i = 0; i < pattern_length; i++) {
            if (!text->good() || !pattern->good() || (text->peek() != pattern->peek())) {
                result = false;
                break;
            }

            text->ignore();
            pattern->ignore();
        }

        // Rewind
        rewinder();

        return result;
    }

    std::optional<size_t> BoyerMooreHorspoolStringSearch::next() {
        typename std::istream::pos_type p_len;
        p_len = getStreamLenght(pattern);

        typename std::istream::pos_type t_rewind;
        t_rewind = text->tellg();

        while (text->good()) {
            if (same(p_len)) {
                text->seekg(static_cast<size_t>(t_rewind) + 1);
                return std::optional<size_t>(t_rewind);
            } else {
                text->seekg(static_cast<size_t>(p_len) - 1, std::ios::cur);
                text->seekg(static_cast<size_t>(t_rewind) + bad_char[text->peek()]);
                t_rewind = text->tellg();
            }
        }

        if (text->eof()) {
            return std::optional<size_t>();
        } else {
            throw std::runtime_error("An error occured while running the string search.");
        }
    }
}
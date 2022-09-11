/**
 * @file bmh.hpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of Boyer-Moore-Horspool algorithm
 * @version 0.1
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BMH__HPP__
#define __BMH__HPP__

#include "base_string_search.hpp"

#include <vector>

namespace string_search {
    class BoyerMooreHorspoolStringSearch : public BaseStringSearch {
        std::vector<size_t> bad_char;

        void makeBadCharTable();

        virtual bool same(size_t pattern_length);
    public:
        BoyerMooreHorspoolStringSearch(
            std::unique_ptr<std::istream> text,
            std::unique_ptr<std::istream> pattern
        );
    
        std::optional<size_t> next() override;
    };
}

#endif // __BMH__HPP__
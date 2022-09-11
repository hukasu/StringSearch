/**
 * @file bm.hpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of Boyer-Moore algorithm
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BM__HPP__
#define __BM__HPP__

#include "base_string_search.hpp"

#include <vector>

namespace string_search {
    class BoyerMooreStringSearch : public BaseStringSearch {
        std::vector<size_t> bad_char;
        std::vector<size_t> good_preffix;

        typename std::istream::pos_type getStreamLenght(std::unique_ptr<std::istream> &stream);

        void makeBadCharTable();
        void makeGoodPrefixTable();
    public:
        BoyerMooreStringSearch(
            std::unique_ptr<std::istream> text,
            std::unique_ptr<std::istream> pattern
        );
    
        std::optional<size_t> next() override;
    };
}

#endif // __BM__HPP__
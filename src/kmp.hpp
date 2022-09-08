/**
 * @file kmp.hpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of Knuth–Morris–Pratt algorithm
 * @version 0.1
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __KMP__HPP__
#define __KMP__HPP__

#include "base_string_search.hpp"

#include <vector>

namespace string_search {
    class KnuthMorrisPrattStringSearch : public BaseStringSearch {
        std::vector<int64_t> table;

        void buildTable();
        static std::unique_ptr<std::istream> seekAndPeek(
            std::unique_ptr<std::istream> stream,
            std::istream::pos_type pos,
            std::istream::char_type &var
        );
    public:
        KnuthMorrisPrattStringSearch(std::unique_ptr<std::istream> search, std::unique_ptr<std::istream> word);
    
        std::optional<size_t> next() override;

        const std::vector<int64_t>& getTable() const;
    };
}

#endif // __KMP__HPP__
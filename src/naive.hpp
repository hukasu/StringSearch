/**
 * @file naive.hpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Implementation of naive string search
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __NAIVE__HPP__
#define __NAIVE__HPP__


#include "base_string_search.hpp"

#include <vector>

namespace string_search {
    class NaiveStringSearch : public BaseStringSearch {
    public:
        NaiveStringSearch(std::unique_ptr<std::istream> search, std::unique_ptr<std::istream> word);
    
        std::optional<size_t> next() override;
    };
}

#endif // __NAIVE__HPP__
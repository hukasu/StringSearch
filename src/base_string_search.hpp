/**
 * @file base_string_search.hpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Base class for string search algorithms
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BASE__STRING__SEARCH__HPP__
#define __BASE__STRING__SEARCH__HPP__

#include <memory>
#include <istream>

#include <optional>

namespace string_search {
    class BaseStringSearch {
    protected:
        std::unique_ptr<std::istream> search;
        std::unique_ptr<std::istream> word;

    public:
        BaseStringSearch(std::unique_ptr<std::istream> search, std::unique_ptr<std::istream> word) :
            search(std::move(search)),
            word(std::move(word))
        {};

        virtual std::optional<size_t> next() = 0;
    };
}

#endif // __BASE__STRING__SEARCH__HPP__
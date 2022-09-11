/**
 * @file base_string_search.cpp
 * @author Lucas Farias (lucasfnf@gmail.com)
 * @brief Base class for string search algorithms
 * @version 0.1
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "base_string_search.hpp"

namespace string_search {
    typename std::istream::pos_type BaseStringSearch::getStreamLenght(
        std::unique_ptr<std::istream> &stream
    ) {
        typename std::istream::pos_type len, rewind;
        rewind = stream->tellg();
        stream->seekg(0, std::ios::end);
        len = stream->tellg();
        stream->seekg(rewind, std::ios::beg);
        return len;
    }
}
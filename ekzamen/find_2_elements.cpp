//
// Created by USER1 on 10.01.2022.
//
#include <unordered_map>

template <typename Iterator, typename T>
std::pair<bool, std::pair<Iterator, Iterator> > a(Iterator first, Iterator last, T c) {
    auto begin = first;
    auto end = last;

    while (begin != end) {
        if (*begin + *end == c) {
            return std::make_pair(true, std::make_pair(begin, end));
        }
        else if (*begin + *end < c) {
            ++begin;
        } else {
            --end;
        }
    }

    return std::make_pair(false, std::make_pair(first, last));
}
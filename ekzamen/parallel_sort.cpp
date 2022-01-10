//
// Created by USER1 on 10.01.2022.
//

#include <iostream>

#include <vector>
#include <thread>
#include <algorithm>

template<class IT, size_t MinFragmentSize=4>
void MultiThreadingSort(IT first, IT last) {
    size_t distance = std::distance(first, last); //считаем, сколько элементов
    IT half = first + distance / 2; // нашли середину

    if (distance/2 < MinFragmentSize) {
        std::sort(first, half);
        std::sort(half, last);
    } else {
        std::thread thread(MultiThreadingSort<IT, MinFragmentSize>, first, half);
        MultiThreadingSort<IT, MinFragmentSize>(half, last);
        thread.join();
    }

    std::vector<typename IT::value_type> merged(distance);
    std::merge(first, half, half, last, merged.begin());

    for (const auto& item : merged) {
        if (first == last) break;

        *first = item;
        ++first;
    }
}

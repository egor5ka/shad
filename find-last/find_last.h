#pragma once

#include <stdexcept>

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator iter = last;
    for (Iterator it = first; it != last; ++it) {
        if (*it == val) {
            iter = it;
        }
    }
    return iter;
}

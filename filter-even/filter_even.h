#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

inline void FilterEven(std::vector<int> *data) {
    auto is_even = [](int n) {
        return n % 2 == 0;
    };

    data->erase(std::remove_if(data->begin(), data->end(), is_even), data->end());
}

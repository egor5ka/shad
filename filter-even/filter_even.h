#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

inline void FilterEven(std::vector<int> *data) {
    // data -> erase(std::remove_if(data->begin(), data->end(),
    //     [](int i){ return i % 2 != 0; }), data->end());

    // for (size_t i = 0; i < data->size();) {
    //     if ((*data)[i] % 2 != 0) {
    //         data -> erase(data->begin() + i);
    //     } else {
    //         ++i;
    //     }
    // }

    size_t write = 0;

    for (size_t read = 0; read < data->size(); ++read) {
        if ((*data)[read] % 2 == 0) {
            (*data)[write] = (*data)[read];
            ++write;
        }
    }
    data -> resize(write);
}

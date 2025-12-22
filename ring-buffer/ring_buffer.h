#pragma once

#include <cstddef>
#include <vector>

class RingBuffer {
public:
    explicit RingBuffer(size_t capacity) : capacity_(capacity), data_(capacity) {
    }

    size_t Size() const {
        return size_;
    }

    bool Empty() const {
        if (size_ != 0) {
            return false;
        }
        return true;
    }

    bool TryPush(int element) {
        if (size_ < capacity_) {
            data_[tail_] = element;
            tail_ = (tail_ + 1) % capacity_;
            ++size_;
            return true;
        }
        return false;
    }

    bool TryPop(int *element) {
        if (size_ != 0) {
            *element = data_[head_];
            head_ = (head_ + 1) % capacity_;
            --size_;

            return true;
        }
        return false;
    }
private:
    int head_ = 0;
    int tail_ = 0;
    int size_ = 0;
    int capacity_ = 0;
    std::vector<int> data_;
};

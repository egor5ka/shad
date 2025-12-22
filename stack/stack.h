#pragma once

#include <cstdint>
#include <vector>

class Stack {
public:
    void Push(int x) {
        stack_.push_back(x);
    }

    bool Pop() {
        if (stack_.empty()) {
            return false;
        }
        stack_.pop_back();
        return true;
    }

    int Top() const {
        if (stack_.empty()) {
            return 0;
        }
        return stack_.back();
    }

    bool Empty() const {
        if (stack_.empty()) {
            return true;
        }
        return false;
    }

    size_t Size() const {
        return stack_.size();
    }
private:
    std::vector<int> stack_;
};

#pragma once

#include <iostream>

struct State {
    std::string* data_;
    int ref_count_;
    size_t size_;
    size_t capacity_;

    State()
        : data_(nullptr)
        , ref_count_(1)
        , size_(0)
        , capacity_(0){}

    explicit State(int size)
        : data_(new std::string[size])
        , ref_count_(1)
        , size_(size)
        , capacity_(size) {}

    explicit State(const State& initial)
        : data_(new std::string[initial.capacity_])
        , ref_count_(1)
        , size_(initial.size_)
        , capacity_(initial.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = initial.data_[i];
        }
    }

    ~State() {
        delete[] data_;
    }
};

class COWVector {
public:
    COWVector()
        : state_(new State()) {}

    COWVector(int size)
        :state_(new State(size)) {
    }

    COWVector(const COWVector& other)
        : state_(other.state_) {
        ++state_->ref_count_;
    }

    ~COWVector() {
        if (--state_->ref_count_ == 0) {
            delete state_;
        }
    }

    COWVector& operator=(const COWVector& other) {
        if (this != &other) {
            if (--state_->ref_count_ == 0) {
                delete state_;
            }
            state_ = other.state_;
            ++state_->ref_count_;
        }
        return *this;
    }

    size_t Size() const {
        return state_->size_;
    }

    void Resize(size_t size) {
        if (state_->ref_count_ > 1) {
            detach_on_write();
        }

        if (size > state_->capacity_) {
            detach_on_write(size);
        }
        state_->size_ = size;
    }

    const std::string& Get(size_t at) {
        return state_->data_[at];
    }

    const std::string& Back() {
        return state_->data_[state_->size_ - 1];
    }

    void detach_on_write(size_t target_capacity = 0) {
        size_t new_cap = (target_capacity > state_->capacity_) ? target_capacity : state_->capacity_;

        auto new_state = new State(new_cap);

        new_state->size_ = state_->size_;

        for (size_t i = 0; i < state_->size_; ++i) {
            new_state->data_[i] = state_->data_[i];
        }

        if (--state_->ref_count_ == 0) {
            delete state_;
        }

        state_ = new_state;
    }

    void PushBack(const std::string& value) {
        if (state_->ref_count_ > 1 || state_->size_ == state_->capacity_) {

            size_t new_cap = state_->capacity_;

            if (state_->size_ == state_->capacity_) {
                new_cap = (state_->capacity_ == 0) ? 1 : state_->capacity_ * 2;
            }

            detach_on_write(new_cap);
        }

        state_->data_[state_->size_++] = value;
    }

    void Set(size_t at, const std::string& value) {
        if (state_->ref_count_ > 1) {
            detach_on_write();
        }

        state_->data_[at] = value;
    }

private:
    State* state_;
};
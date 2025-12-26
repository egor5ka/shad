#pragma once

#include <iostream>



class Vector {
public:
    Vector()
        : data_(nullptr)
        , size_(0)
        , capacity_(0) {}

    explicit Vector(size_t size)
        : data_(new int[size])
        , size_(size)
        , capacity_(size) {

        for (size_t i = 0; i < size; i++)
            data_[i] = 0;
    }

    Vector(std::initializer_list<int> il) {
        data_ = new int[il.size()];
        size_ = il.size();
        capacity_ = il.size();

        int i = 0;
        for (auto it : il) {
            data_[i++] = it;
        }
    }

    Vector(const Vector& other) {
        data_ = new int[other.size_];
        size_ = other.size_;
        capacity_ = other.capacity_;

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector(Vector&& other) {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
    }

    ~Vector() {
        delete[] data_;
    }

    Vector& operator=(Vector& other) {
        Swap(other);
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            Swap(other);
        }
        return *this;
    }

    void Swap(Vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);

    }

    int& operator[](int i) {
        return data_[i];
    }

    const int& operator[](int i) const {
        return data_[i];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(int value) {
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
            Vector tmp(new_capacity);
            tmp.size_ = size_;

            for (size_t i = 0; i < size_; ++i) {
                tmp.data_[i] = data_[i];
            }
            tmp.data_[size_] = value;
            ++tmp.size_;

            Swap(tmp);

        } else {
            data_[size_++] = value;
        }
    }

    void PopBack() {
        if (size_ == 0) {
            return;
        }
        --size_;
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            Vector tmp(new_capacity);
            for (size_t i = 0; i < size_; ++i) {
                tmp.data_[i] = data_[i];
            }
            tmp.size_ = size_;
            Swap(tmp);
        }
    }

    class Iterator {
        public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int*;
        using reference = int&;

        Iterator() : current_(nullptr) {}
        explicit Iterator(int* current) : current_(current) {}

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator cpy(*this);
            ++current_;
            return cpy;
        }

        Iterator& operator--() {
            --current_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator cpy(*this);
            --current_;
            return cpy;
        }

        Iterator& operator+=(int offset) {
            current_ += offset;
            return *this;
        }

        Iterator& operator-=(int offset) {
            current_ -= offset;
            return *this;
        }

        Iterator operator+(int offset) {
            return Iterator(current_ + offset);
        }

        Iterator operator-(int offset) {
            return Iterator(current_ - offset);
        }

        ptrdiff_t operator-(const Iterator& other) const {
            return current_ - other.current_;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

        int& operator*() {
            return *current_;
        }

        int* operator->() {
            return current_;
        }

        private:
            int* current_;
    };

    Iterator Begin() const {
        return Iterator(data_);
    }

    Iterator End() const {
        return Iterator(data_ + size_);
    }

    Iterator begin() const {
        return Begin();
    }

    Iterator end() const {
        return End();
    }


private:
    int* data_;
    size_t size_;
    size_t capacity_;
};

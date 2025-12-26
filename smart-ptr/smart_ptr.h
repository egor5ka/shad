#pragma once

#include <string>

#include "smart_ptr.h"

struct Block {
    int strong_counter;
    int weak_counter;
};

class WeakPtr;

class SharedPtr {
public:
    SharedPtr()
        : counter_(new Block{1, 0}) {};

    SharedPtr(std::string* pointer)
        : pointer_(pointer)
        , counter_(new Block{1, 0}) {}

    SharedPtr(const SharedPtr& rhs) {
        pointer_ = rhs.pointer_;
        counter_ = rhs.counter_;
        ++(counter_->strong_counter);
    }

    SharedPtr(SharedPtr&& rhs) {
        pointer_ = rhs.pointer_;
        counter_ = rhs.counter_;
        rhs.pointer_ = nullptr;
        rhs.counter_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& rhs) {
        if (this != &rhs) {
            SharedPtr rhs_copy(rhs);
            Swap(rhs_copy);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& rhs) {
        if (this != &rhs) {
            Swap(rhs);
            rhs.pointer_ = nullptr;
            rhs.counter_ = nullptr;
        }
        return *this;
    }

    bool operator!=(const SharedPtr& rhs) const {
        return pointer_ != rhs.pointer_;
    }

    bool operator==(const SharedPtr& rhs) const {
        return pointer_ == rhs.pointer_;
    }

    std::string& operator*() const {
        return *pointer_;
    }

    void Swap(SharedPtr& rhs) {
        std::swap(pointer_, rhs.pointer_);
        std::swap(counter_, rhs.counter_);
    }

    ~SharedPtr() {
        if (pointer_ == nullptr) {
            return;
        }

        --(counter_->strong_counter);

        if (counter_->strong_counter == 0) {
            delete pointer_;
        }

        if (counter_->weak_counter + counter_->strong_counter == 0) {
            delete counter_;
        }
    }

    SharedPtr(const WeakPtr& rhs);

    std::string* Get() const {
        return pointer_;
    }

    Block* GetСounter() const {
        return counter_;
    }

    void Reset(std::string* ptr = nullptr) {
        SharedPtr tmp(ptr);
        Swap(tmp);
    }

private:
    std::string* pointer_ = nullptr;
    Block* counter_;
};

class WeakPtr {
public:
    WeakPtr()
        : pointer_(nullptr)
        , counter_(nullptr) {}

    WeakPtr(const WeakPtr& rhs) {
        pointer_ = rhs.pointer_;
        counter_ = rhs.counter_;
        if (counter_) {
            ++counter_->weak_counter;
        }
    }

    WeakPtr(WeakPtr&& rhs) {
        pointer_ = rhs.pointer_;
        counter_ = rhs.counter_;
        rhs.pointer_ = nullptr;
        rhs.counter_ = nullptr;
    }

    WeakPtr(const SharedPtr& ptr) {
        pointer_ = ptr.Get();
        counter_ = ptr.GetСounter();
        if (counter_) {
            ++counter_->weak_counter;
        }
    }

    WeakPtr& operator=(const WeakPtr& rhs) {
        if (this != &rhs) {
            WeakPtr tmp(rhs);
            Swap(tmp);
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& rhs) noexcept {
        if (this != &rhs) {
            Swap(rhs);
        }
        return *this;
    }

    bool IsExpired() const {
        if (counter_ == nullptr) {
            return true;
        }
        return counter_->strong_counter == 0;
    }

    ~WeakPtr() {
        if (counter_ == nullptr) {
            return;
        }
        --(counter_->weak_counter);

        if (counter_->strong_counter + counter_->weak_counter == 0) {
            delete counter_;
        }
    }

    void Swap(WeakPtr& rhs) {
        std::swap(pointer_, rhs.pointer_);
        std::swap(counter_, rhs.counter_);
    }

    SharedPtr Lock() {
        if (IsExpired()) {
            return SharedPtr();
        }
        return SharedPtr(*this);
    }

    std::string* Get() const {
        return pointer_;
    }

    Block* GetCounter() const {
        return counter_;
    }

private:
    std::string* pointer_;
    Block* counter_;
};

inline SharedPtr::SharedPtr(const WeakPtr& rhs) {
    if (rhs.IsExpired()) {
        pointer_ = nullptr;
        counter_ = new Block{1, 0};
    } else {
        pointer_ = rhs.Get();
        counter_ = rhs.GetCounter();
        ++(counter_->strong_counter);
    }
}

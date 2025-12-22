#pragma once

#include <string>
#include <cstring>

class StringView {
public:
    explicit StringView(const std::string& str, size_t pos = 0, size_t len = std::string::npos) {
        if (pos > str.size()) {
            watcher_ = nullptr;
            size_ = 0;
            len = 0;
            return;
        }
        watcher_ = str.data() + pos;
        size_ = std::min(len, str.size() - pos);
    }

    explicit StringView(const char* ch)
        : watcher_(ch)
        , size_(strlen(ch)) {}

    explicit StringView(const char* ptr, const int len)
        : watcher_(ptr)
        , size_(len) {}

    const char& operator[](const int i) const {
        return watcher_[i];
    }

    int Size() const {
        return size_;
    }

private:
    const char* watcher_ = nullptr;
    size_t size_ = 0;
};

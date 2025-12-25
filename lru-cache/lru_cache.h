#pragma once

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

struct Node {
    std::string key;
    std::string value;

    Node(const std::string& k,const std::string& v) : key(k), value(v) {}
};

class LruCache {
public:
    LruCache(size_t max_size)
        : max_size_(max_size) {
    }

    void Set(const std::string& key, const std::string& value) {
        auto it = map_.find(key);

        if (it != map_.end()) {
            it->second->value = value;
            list_.splice(list_.begin(), list_, it->second);
            return;
        }

        if (max_size_ == map_.size()) {
            auto& least_node = list_.back();
            map_.erase(least_node.key);
            list_.pop_back();
        }

        list_.emplace_front(key, value);
        map_[key] = list_.begin();
    }

    bool Get(const std::string& key, std::string* value) {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return false;
        }

        list_.splice(list_.begin(), list_, it->second);

        *value = it->second->value;
        return true;
    }

private:
    std::unordered_map<std::string, std::list<Node>::iterator> map_;
    std::list<Node> list_;
    size_t max_size_;
};
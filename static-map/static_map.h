#pragma once

#include <vector>
#include <string>
#include <utility>

class StaticMap {
public:
    explicit StaticMap(const std::vector<std::pair<std::string, std::string>>& items)
        : map_(items) {
        std::sort(map_.begin(), map_.end());
    }

    bool Find(const std::string& key, std::string* value) const {
        auto it = std::lower_bound(map_.begin(), map_.end(),
            std::make_pair(key, value),
            [](const auto& a, const auto& b) {return a.first < b.first;});

        if (it != map_.end() && it->first == key) {
            *value = it->second;
            return true;
        }
        return false;
    }

private:
    std::vector<std::pair<std::string, std::string>> map_;
};

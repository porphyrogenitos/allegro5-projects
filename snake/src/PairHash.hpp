#pragma once

#include <utility>
#include <unordered_set>

/**
 * @brief Hash function so that Tiles (which are std::pairs) can be stored in a set.
 * 
 */
namespace std {
    template<typename X, typename Y>
    struct hash<std::pair<X, Y>> {
        std::size_t operator()(const std::pair<X, Y> &pair) const {
            return std::hash<X>()(pair.first) ^ std::hash<Y>()(pair.second);
        }
    };
}
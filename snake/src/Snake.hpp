#pragma once

#include <iostream>
#include <string>
#include <array>
#include <utility>
#include "Direction.hpp"

#define SNAKE_INIT_LEN 5

using Tile = std::pair<int, int>;

class Snake {
    private:
        int length {};
        Direction head_dir {};
        std::array<Tile, 200> segments {}; // Tile positions of segments.
        
    public:
        /**
         * @brief Construct a new Snake object
         * 
         * @param init_dir The initial direction of the snake.
         * @param head_r The tile row
         * @param head_c The tile column
         */
        Snake(Direction init_dir, int head_r, int head_c) {
            length = SNAKE_INIT_LEN;
            head_dir = init_dir;
            segments[0].first = head_r;
            segments[0].second = head_c;
            for (int i = 1; i < length; i++) {
                segments[i].first = segments[0].first;
                segments[i].second = segments[i - 1].second - 1;
            }
        }

        /**
         * @brief Get the length of the Snake
         * 
         * @return int 
         */
        int get_length() const { return length; }

        Direction get_direction() const { return head_dir; }

        Tile get_head_tile() const { return segments[0]; }

        Tile get_segment_position(int index) const;

        void move();

        void update_head_dir(Direction new_dir);

        void grow();

        void print();


};
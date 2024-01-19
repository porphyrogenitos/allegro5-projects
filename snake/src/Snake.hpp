#pragma once

#include <iostream>
#include <string>
#include <array>
#include "Direction.hpp"

#define SNAKE_INIT_LEN 5

class Snake {
    private:
        int length {};
        int head_r {}; // Row position of head (in TileGrid)
        int head_c {}; // Column position of head (in TileGrid)
        std::array<Direction, 200> direction_arr {};
        
    public:
        /**
         * @brief Construct a new Snake object
         * 
         * @param init_dir The initial direction of the snake.
         */
        Snake(Direction init_dir, int head_r, int head_c) {
            length = 5;
            this->head_r = head_r;
            this->head_c = head_c;
            for (int i = 0; i < length; i++) {
                direction_arr[i] = init_dir;
            }
        }

        /**
         * @brief Get the length of the Snake
         * 
         * @return int 
         */
        int get_length() const { return length; }

        int get_head_r() const { return head_r; }

        int get_head_c() const { return head_c; }

        Direction get_segment_direction(int index) const;

        Direction get_segment_position(int index) const;

        void move();

        void update_head_dir(Direction new_dir);

        void grow();

        void print();


};
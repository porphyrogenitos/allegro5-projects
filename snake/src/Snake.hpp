#pragma once

#include <iostream>
#include <string>
#include <array>
#include "Direction.hpp"

#define SNAKE_INIT_LEN 5

class Snake {
    private:
        int length {};
        std::array<Direction, 100> direction_arr {};
        
    public:
        /**
         * @brief Construct a new Snake object
         * 
         * @param init_dir The initial direction of the snake.
         */
        Snake(Direction init_dir) {
            length = 5;
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

        const std::array<Direction, 100>& get_direction_arr() const;

        Direction get_segment_direction(int index) const;

        Direction get_segment_position(int index) const;

        void move();

        void update_head_dir(Direction new_dir);

        void grow();

        void print();


};
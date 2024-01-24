#pragma once

#include <iostream>
#include <string>
#include <array>
#include <utility>
#include "Direction.hpp"
#include "PairHash.hpp"

#define SNAKE_INIT_LEN 5

using Tile = std::pair<int, int>;

class Snake {
    private:
        int length {};
        Direction head_dir {};
        std::array<Tile, 200> segments {}; // Tile positions of segments.
        std::unordered_set<Tile> occupied_tiles;
        
    public:
        /**
         * @brief Construct a new Snake object
         * 
         * @param init_dir The initial direction of the snake.
         * @param head_r The tile row
         * @param head_c The tile column
         */
        Snake(Direction init_dir, int head_r, int head_c);

        /**
         * @brief Get the length of the Snake
         * 
         * @return int 
         */
        int get_length() const { return length; }

        Direction get_direction() const { return head_dir; }

        Tile get_head_tile() const { return segments[0]; }

        Tile get_segment_position(int index) const;

        bool occupies_tile(Tile tile) { return occupied_tiles.find(tile) != occupied_tiles.end(); }

        void move();

        void update_head_dir(Direction new_dir);

        void grow();

        void print();


};
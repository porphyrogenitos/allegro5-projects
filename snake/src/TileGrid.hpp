#pragma once

#include <iostream>
#include <utility>
#include <vector>

enum class Tile {
    empty,
    snake_head,
    snake_body,
    food,
};

std::string tile_to_string(Tile tile) {
    switch (tile) {
        case Tile::empty:
            return "E";
        case Tile::snake_head:
            return "H";
        case Tile::snake_body:
            return "B";
        case Tile::food:
            return "F";
        default:
            return "";
    }
}

struct TileGrid {

    int board_width {}; // Width of the board in pixels.
    int board_height {}; // Height of the board in pixels.

    int num_rows {};
    int num_cols {};

    std::vector<std::vector<Tile>> board {};

    TileGrid(int board_width, int board_height, int tile_width) {
        this->board_width = board_width;
        this->board_height = board_height;

        num_rows = board_height / tile_width;
        num_cols = board_width / tile_width;

        std::cout << "Num rows: " << std::to_string(num_rows) << "\n";
        std::cout << "Num cols: " << std::to_string(num_cols) << "\n";

        // Initialize board with correctly sized dimensions.
        board.resize(num_rows, std::vector<Tile>(num_cols, Tile::empty));

        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                std::cout << tile_to_string(board[i][j]) << " ";
            }
            std::cout << std::endl;
        }
    }


    /**
     * @brief Returns the (x,y) center of the tile at (row, column).
     * 
     * @param row 
     * @param column 
     * @return std::pair<int, int> 
     */
    std::pair<int, int> convert_rc_to_xy(int row, int column) {

    }

    Tile get_tile(int row, int col) {
        if (row >= num_rows || col >= num_cols)
            return Tile::empty;
        else
            return board[row][col];
    }

    void update_tile(int row, int col, Tile tile) {
        if (row >= num_rows || col >= num_cols)
            return;
        else
            board[row][col] = tile;
    }

    void clear_tiles() {
        for (int i = 0; i < num_rows; i++)
            for (int j = 0; j < num_cols; j++)
                board[i][j] = Tile::empty;
    }

    std::string to_string() {
        std::string str = "";
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                str += tile_to_string(board[i][j]) + " ";
            }
            str += "\n";
        }

        return str;
    }

};

int calculate_num_sections(int piece_length, int section_length) {
    return piece_length / section_length;
}
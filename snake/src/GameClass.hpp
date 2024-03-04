#pragma once

#include <iostream>
#include <utility>
#include <unordered_set>
#include <functional>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Platform.hpp"
#include "GameData.hpp"
#include "Constants.hpp"
#include "Snake.hpp"
#include "Direction.hpp"
#include "Food.hpp"

/**
 * @brief Object for controlling snake game play and drawing.
 * 
 */
class GameClass {
private:
    Platform* platform;
    GameData* game_data;
    std::function<void()> exit_handler;
    std::function<void()> game_over_handler;
    int x {};
    int y {};
    int width {};
    int height {};

    int tilegrid_num_rows {};
    int tilegrid_num_cols {};

    bool redraw {false};
    bool done {false};
    bool should_grow {false};
    bool food_eaten {false};

    Snake snake {Direction::east, 10, 10};
    Food food {5, 5};

    /**
     * @brief Debugging function that prints all tile coordinates in tiles.
     * 
     * @param tiles 
     */
    void print_tileset(std::unordered_set<Tile> tiles);

    /**
     * @brief Draws food onto display, based on food's row and column tile coordinate.
     * 
     * @param food 
     * @param isVisible Whether the food should actually be visible on the display.
     */
    void display_food(Food food, bool isVisible);

    /**
     * @brief Moves food to match coordinates of to_tile.
     * 
     * @param food 
     * @param to_tile 
     */
    void move_food(Food& food, Tile to_tile);

    /**
     * @brief Calls move function on snake.
     * 
     * @param snake 
     */
    void move_snake(Snake& snake);

    /**
     * @brief Determines if tile (r1, c1) and tile (r2, c2) are the same tile.
     * 
     * @param r1 
     * @param c1 
     * @param r2 
     * @param c2 
     * @return true if (r1, c1) == (r2, c2)
     * @return false otherwise
     */
    bool is_collision(int r1, int c1, int r2, int c2);

    /**
     * @brief Draws snake onto display. The snake head is red while the body is green.
     * 
     * @param snake 
     * @param isVisible Whether the snake should actually be visible on the display.
     */
    void display_snake(Snake snake, bool isVisible);

    /**
     * @brief Temporary function for making the grid of tiles visible.
     * 
     * @param num_rows 
     * @param num_cols 
     */
    void draw_grid(int num_rows, int num_cols);

    /**
     * @brief Find a random tile not occupied by snake.
     * 
     * @param snake 
     * @return Tile 
     */
    Tile get_random_empty_tile(Snake snake);

    /**
     * @brief Check if the snake has died.
     * 
     * @param snake 
     * @return true if the snake is outside the bounds or intersects with itself.
     * @return false if the snake is within the bounds and does not intersect with itself.
     */
    bool check_death(Snake snake);

public:
    GameClass(Platform* platform, 
                GameData* game_data, 
                std::function<void()> exit_handler, 
                std::function<void()> game_over_handler);

    ~GameClass();

    /**
     * @brief Set the pixel dimensions of the game on this display.
     * 
     * @param x Top left x-coordinate (in pixels)
     * @param y Top left y-coordinate (in pixels)
     * @param width (in pixels)
     * @param height (in pixels)
     */
    void set_dimensions(int x, int y, int width, int height);

    void tick();

    void draw();
};
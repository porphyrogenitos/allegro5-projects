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

/* TODO: Add x, y, width, and height ints so that it can be drawn as a section of the display.
    This is important because PlayState will have a top band containing the score and other info,
    while the Snake game itself (GameClass) will be displayed underneath.
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

    void print_tileset(std::unordered_set<Tile> tiles);

    void display_food(Food food, bool isVisible);

    void move_food(Food& food, Tile to_tile);

    void move_snake(Snake& snake);

    bool is_collision(int r1, int c1, int r2, int c2);

    void display_snake(Snake snake, bool isVisible);

    void draw_grid(int num_rows, int num_cols);

    Tile get_random_empty_tile(Snake snake);

    bool check_death(Snake snake);

public:
    GameClass(Platform* platform, 
                GameData* gamed_data, 
                std::function<void()> exit_handler, 
                std::function<void()> game_over_handler);

    ~GameClass();

    void set_dimensions(int x, int y, int width, int height);

    void loop();

    void tick();

    void draw();
};
#pragma once

#include <iostream>
#include <utility>
#include <unordered_set>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Constants.hpp"
#include "Snake.hpp"
#include "Direction.hpp"
#include "Food.hpp"

class GameHost;

class GameClass {
private:
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT* event {};
    unsigned char* key;
    GameHost* gamehost;

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
    GameClass(GameHost* gamehost);

    ~GameClass();

    void loop();

    void tick();

    void draw();
};
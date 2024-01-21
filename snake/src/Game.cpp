#include <iostream>
#include <utility>
#include <unordered_set>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Snake.cpp"
#include "Direction.hpp"
#include "Food.hpp"


const int DISP_WIDTH = 640;
const int DISP_HEIGHT = 480;
const int TILE_WIDTH = 20;

const int KEY_SEEN = 1;
const int KEY_RELEASED = 2;

int tilegrid_num_rows = DISP_HEIGHT / TILE_WIDTH;
int tilegrid_num_cols = DISP_WIDTH / TILE_WIDTH;

namespace std {
    template<typename X, typename Y>
    struct hash<std::pair<X, Y>> {
        std::size_t operator()(const std::pair<X, Y> &pair) const {
            return std::hash<X>()(pair.first) ^ std::hash<Y>()(pair.second);
        }
    };
}
std::unordered_set<Tile> occupied_tiles;

void print_tileset(std::unordered_set<Tile> tiles) {
    for (auto iter = tiles.begin(); iter != tiles.end(); ++iter) {
		std::cout << "(" << std::to_string(iter->first) << "," << std::to_string(iter->second) << ") "; 
    }
    std::cout << std::endl;
}

void display_food(Food food, bool isVisible) {
    int x1 = food.col * TILE_WIDTH;
    int y1 = food.row * TILE_WIDTH;
    int x2 = (food.col + 1) * TILE_WIDTH;
    int y2 = (food.row + 1) * TILE_WIDTH;

    int center_x = (x1 + x2) / 2;
    int center_y = (y1 + y2) / 2;
    float rad = TILE_WIDTH / 2;

    if (isVisible)
        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(50, 100, 10));
    else
        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(0, 0, 0));
}

void move_food(Food& food, int row, int col) {
    food.row = row;
    food.col = col;
}

bool is_collision(int r1, int c1, int r2, int c2) {
    return (r1 == r2) && (c1 == c2);
}


void display_snake(Snake snake, bool isVisible) {
    int head_row = snake.get_head_tile().first;
    int head_col = snake.get_head_tile().second;

    // Draw head.
    int head_x1 = head_col * TILE_WIDTH;
    int head_y1 = head_row * TILE_WIDTH;
    int head_x2 = (head_col + 1) * TILE_WIDTH;
    int head_y2 = (head_row + 1) * TILE_WIDTH;

    int center_x = (head_x1 + head_x2) / 2;
    int center_y = (head_y1 + head_y2) / 2;
    float rad = TILE_WIDTH / 2;
    if (isVisible)
        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(255, 0, 0)); // Red head
    else
        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(0, 0, 0));

    ALLEGRO_COLOR body_color = al_map_rgb(0, 255, 0); // Green
    if (!isVisible)
        body_color = al_map_rgb(0, 0, 0); // Black (not visible)

    // Draw body.
    for (int index = 1; index < snake.get_length(); index++) {
        Tile pos = snake.get_segment_position(index);
        int cur_row = pos.first;
        int cur_col = pos.second;

        int x1 = cur_col * TILE_WIDTH;
        int y1 = cur_row * TILE_WIDTH;
        int x2 = (cur_col + 1) * TILE_WIDTH;
        int y2 = (cur_row + 1) * TILE_WIDTH;

        int center_x = (x1 + x2) / 2;
        int center_y = (y1 + y2) / 2;

        al_draw_filled_circle(center_x, center_y, rad, body_color);
    }
}

/**
 * @brief Temporary function for making the grid of tiles visible.
 * 
 * @param num_rows 
 * @param num_cols 
 */
void draw_grid(int num_rows, int num_cols) {
    for (int row = 0; row < num_rows; row++) {
        int y = row * TILE_WIDTH;
        al_draw_line(0, y, DISP_WIDTH, y, al_map_rgb(255, 0, 0), 1.0);
    }

    for (int col = 0; col < num_cols; col++) {
        int x = col * TILE_WIDTH;
        al_draw_line(x, 0, x, DISP_HEIGHT, al_map_rgb(255, 0, 0), 1.0);
    }
}

Tile get_random_empty_tile() {
    
    int rand_row = rand() % (tilegrid_num_rows - 1);
    int rand_col = rand() % (tilegrid_num_cols - 1);

    std::pair<int, int> pair {rand_row, rand_col};

    while (occupied_tiles.find(pair) != occupied_tiles.end()) {
        rand_row = (rand_row + 1) % rand_row;

        if (rand_row % 3 == 0)
            rand_col = (rand_col + 1) % rand_col;

        pair.first = rand_row;
        pair.second = rand_col;
    }

    return pair;
}

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_TIMER* timer { al_create_timer(ALLEGRO_BPS_TO_SECS(1.0))};
    ALLEGRO_EVENT_QUEUE* event_queue {al_create_event_queue()};

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    ALLEGRO_DISPLAY* display = al_create_display(DISP_WIDTH, DISP_HEIGHT);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    bool redraw {false};
    bool done {false};
    bool should_grow {false};
    bool food_eaten {false};

    ALLEGRO_EVENT event {};
    al_start_timer(timer);
    

    Snake snake {Direction::east, 10, 10};
    snake.print();

    Food food {5, 5};
    occupied_tiles.insert(Tile{food.row, food.col});
    print_tileset(occupied_tiles);


    //draw_snake(snake);
    display_snake(snake, true);
    display_food(food, true);
    draw_grid(tilegrid_num_rows, tilegrid_num_cols);
    al_flip_display();


    while (true) {
        al_wait_for_event(event_queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_UP])
                    snake.update_head_dir(Direction::north);
                else if(key[ALLEGRO_KEY_DOWN])
                    snake.update_head_dir(Direction::south);
                else if(key[ALLEGRO_KEY_LEFT])
                   snake.update_head_dir(Direction::west);
                else if(key[ALLEGRO_KEY_RIGHT])
                    snake.update_head_dir(Direction::east);

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                if (is_collision(snake.get_head_tile().first, snake.get_head_tile().second, food.row, food.col)) {
                    should_grow = true;
                    food_eaten = true;
                }

                redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_event_queue_is_empty(event_queue)) {
            display_snake(snake, false);

            if (should_grow) {
                snake.grow();
                //snake.get
                should_grow = false;
            }

            // TODO: Might be good to move the following into a function move_snake(Snake snake).
            for (int i = 0; i < snake.get_length(); i++) {
                occupied_tiles.erase(snake.get_segment_position(i));
            }
            snake.move();
            for (int i = 0; i < snake.get_length(); i++) {
                occupied_tiles.insert(snake.get_segment_position(i));
            }

            if (food_eaten) { 
                display_food(food, false);
                Tile old_food_tile = Tile {food.row, food.col};
                std::pair<int, int> rand_tile = get_random_empty_tile();
                move_food(food, rand_tile.first, rand_tile.second);
                occupied_tiles.erase(old_food_tile);
                occupied_tiles.insert(rand_tile);

                print_tileset(occupied_tiles);

                food_eaten = false;
            }
            display_food(food, true);
            display_snake(snake, true);

            draw_grid(tilegrid_num_rows, tilegrid_num_cols);

            al_flip_display();
            
            redraw = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
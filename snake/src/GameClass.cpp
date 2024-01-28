#include "GameClass.hpp"
#include "GameHost.hpp"

GameClass::GameClass(GameHost* gamehost) {
    this->gamehost = gamehost;
    timer = gamehost->get_timer_ptr();
    display = gamehost->get_display_ptr();
    event_queue = gamehost->get_event_queue_ptr();
    key = gamehost->get_key_array();
}

GameClass::~GameClass() {
    gamehost = nullptr;
}

void GameClass::print_tileset(std::unordered_set<Tile> tiles) {
    for (auto iter = tiles.begin(); iter != tiles.end(); ++iter) {
        std::cout << "(" << std::to_string(iter->first) << "," << std::to_string(iter->second) << ") "; 
    }
    std::cout << std::endl;
}

void GameClass::display_food(Food food, bool isVisible) {
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

void GameClass::move_food(Food& food, Tile to_tile) {
    food.row = to_tile.first;
    food.col = to_tile.second;
}

void GameClass::move_snake(Snake& snake) {
    snake.move();
}

bool GameClass::is_collision(int r1, int c1, int r2, int c2) {
    return (r1 == r2) && (c1 == c2);
}


void GameClass::display_snake(Snake snake, bool isVisible) {
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
void GameClass::draw_grid(int num_rows, int num_cols) {
    for (int row = 0; row < num_rows; row++) {
        int y = row * TILE_WIDTH;
        al_draw_line(0, y, DISP_WIDTH, y, al_map_rgb(255, 0, 0), 1.0);
    }

    for (int col = 0; col < num_cols; col++) {
        int x = col * TILE_WIDTH;
        al_draw_line(x, 0, x, DISP_HEIGHT, al_map_rgb(255, 0, 0), 1.0);
    }
}

Tile GameClass::get_random_empty_tile(Snake snake) {
    
    int rand_row = rand() % (tilegrid_num_rows - 1);
    int rand_col = rand() % (tilegrid_num_cols - 1);

    std::pair<int, int> pair {rand_row, rand_col};

    while (snake.occupies_tile(pair)) {
        rand_row = (rand_row + 1) % rand_row;

        if (rand_row % 3 == 0)
            rand_col = (rand_col + 1) % rand_col;

        pair.first = rand_row;
        pair.second = rand_col;
    }

    return pair;
}

bool GameClass::check_death(Snake snake) {

    Tile head = snake.get_segment_position(0);
    if (head.first < 0 || head.first >= tilegrid_num_rows
        || head.second < 0 || head.second >= tilegrid_num_cols) {
\
            return true;
    }

    for (int i = 1; i < snake.get_length(); i++) {
        Tile segment = snake.get_segment_position(i);
        if (head == segment) {
            return true;
        }
    }

    return false;
}

void GameClass::loop() {
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

                // Check if head has collided with food.
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
                should_grow = false;
            }

            move_snake(snake);

            if (food_eaten) { 
                display_food(food, false);
                std::pair<int, int> rand_tile = get_random_empty_tile(snake);
                move_food(food, rand_tile);

                food_eaten = false;
            }
            display_food(food, true);
            display_snake(snake, true);

            draw_grid(tilegrid_num_rows, tilegrid_num_cols);

            if (check_death(snake)) {
                std::cout << "DIED." << std::endl;
                break;
            }

            al_flip_display();
            
            redraw = false;
        }
    }

    gamehost->state_ended();
}
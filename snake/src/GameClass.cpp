#include "GameClass.hpp"

GameClass::GameClass(Platform* platform, GameData* game_data, std::function<void()> exit_handler, std::function<void()> game_over_handler) {
    this->platform = platform;
    this->game_data = game_data;
    this->exit_handler = exit_handler;
    this->game_over_handler = game_over_handler;
}

GameClass::~GameClass() {}

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
    float rad = TILE_WIDTH / 2;
    
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

    int head_row = snake.get_head_tile().first;
    int head_col = snake.get_head_tile().second;

    // Draw head.
    int head_x1 = head_col * TILE_WIDTH;
    int head_y1 = head_row * TILE_WIDTH;
    int head_x2 = (head_col + 1) * TILE_WIDTH;
    int head_y2 = (head_row + 1) * TILE_WIDTH;

    int center_x = (head_x1 + head_x2) / 2;
    int center_y = (head_y1 + head_y2) / 2;
    if (isVisible)
        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(255, 0, 0)); // Red head
    else
        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(0, 0, 0));
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

void GameClass::tick() {
    if(platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_UP))
        snake.update_head_dir(Direction::north);
    else if(platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_DOWN))
        snake.update_head_dir(Direction::south);
    else if(platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_LEFT))
    snake.update_head_dir(Direction::west);
    else if(platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_RIGHT))
        snake.update_head_dir(Direction::east);

    if(platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_ESCAPE))
        //TODO: Rename to handle_escape()
        exit_handler();
            
    // Check if head has collided with food.
    if (is_collision(snake.get_head_tile().first, snake.get_head_tile().second, food.row, food.col)) {
        game_data->current_score++;
        snake.grow();

        std::pair<int, int> rand_tile = get_random_empty_tile(snake);
        move_food(food, rand_tile);
    }

    snake.move();

    // TODO: Right spot for this check?
    if (check_death(snake)) {
        std::cout << "DIED." << std::endl;

        //TODO: Perhaps pass screencap to the state.
        //TODO: Rename to handle_death()
        game_over_handler();
    }
}

void GameClass::draw() {
    display_food(food, true);
    display_snake(snake, true);
    // draw_grid(tilegrid_num_rows, tilegrid_num_cols); 
}
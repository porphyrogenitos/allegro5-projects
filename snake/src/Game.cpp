#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Snake.cpp"
#include "Direction.hpp"
#include "TileGrid.hpp"


const int DISP_WIDTH = 640;
const int DISP_HEIGHT = 480;
const int TILE_WIDTH = 20;


void clear_snake(Snake snake) {

    int cur_row = snake.get_head_r();
    int cur_col = snake.get_head_c();

    for (int index = 1; index < snake.get_length(); index++) {
        Direction pos = snake.get_segment_position(index);
        switch (pos) {
            case Direction::north:
                cur_row -= 1;
                break;
            case Direction::south:
                cur_row += 1;
                break;
            case Direction::east:
                cur_col += 1;
                break;
            case Direction::west:
                cur_col -= 1;
                break;
            default:
                break;
        }

        int x1 = cur_col * TILE_WIDTH;
        int y1 = cur_row * TILE_WIDTH;
        int x2 = (cur_col + 1) * TILE_WIDTH;
        int y2 = (cur_row + 1) * TILE_WIDTH;

        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 0));
    }
}

void draw_snake(Snake snake) {
    int cur_row = snake.get_head_r();
    int cur_col = snake.get_head_c();

    // Draw head.
    int x1 = cur_col * TILE_WIDTH;
    int y1 = cur_row * TILE_WIDTH;
    int x2 = (cur_col + 1) * TILE_WIDTH;
    int y2 = (cur_row + 1) * TILE_WIDTH;

    int center_x = (x1 + x2) / 2;
    int center_y = (y1 + y2) / 2;
    float rad = TILE_WIDTH / 2;
    al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(255, 0, 0));

    // Draw body.
    for (int index = 1; index < snake.get_length(); index++) {
        Direction pos = snake.get_segment_position(index);
        switch (pos) {
            case Direction::north:
                cur_row -= 1;
                break;
            case Direction::south:
                cur_row += 1;
                break;
            case Direction::east:
                cur_col += 1;
                break;
            case Direction::west:
                cur_col -= 1;
                break;
            default:
                break;
        }

        int x1 = cur_col * TILE_WIDTH;
        int y1 = cur_row * TILE_WIDTH;
        int x2 = (cur_col + 1) * TILE_WIDTH;
        int y2 = (cur_row + 1) * TILE_WIDTH;

        int center_x = (x1 + x2) / 2;
        int center_y = (y1 + y2) / 2;
        float rad = TILE_WIDTH / 2;

        al_draw_filled_circle(center_x, center_y, rad, al_map_rgb(0, 255, 0));
    }
}

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

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_TIMER* timer { al_create_timer(ALLEGRO_BPS_TO_SECS(30.0))};
    ALLEGRO_EVENT_QUEUE* event_queue {al_create_event_queue()};

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    ALLEGRO_DISPLAY* display = al_create_display(DISP_WIDTH, DISP_HEIGHT);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    bool redraw {false};
    bool done {false};

    ALLEGRO_EVENT event {};
    al_start_timer(timer);

    TileGrid tilegrid {DISP_WIDTH, DISP_HEIGHT, TILE_WIDTH};

    int tilegrid_num_rows = DISP_HEIGHT / TILE_WIDTH;
    int tilegrid_num_cols = DISP_WIDTH / TILE_WIDTH;
    

    Snake snake {Direction::east, 10, 10};
    snake.update_head_dir(Direction::north);
    snake.print();

    draw_snake(snake);
    draw_grid(tilegrid_num_rows, tilegrid_num_cols);
    al_flip_display();


    while (true) {
        al_wait_for_event(event_queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                //redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                redraw = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_event_queue_is_empty(event_queue)) {
            clear_snake(snake);
            snake.move();

            draw_snake(snake);

            draw_grid(tilegrid_num_rows, tilegrid_num_cols);

            al_flip_display();
            
            redraw = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
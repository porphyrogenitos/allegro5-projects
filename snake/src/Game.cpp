#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Snake.cpp"
#include "Direction.hpp"


const int DISP_WIDTH = 640;
const int DISP_HEIGHT = 480;

// TODO
void draw_snake(Snake snake, int head_x, int head_y) {
    int cur_x = head_x;
    int cur_y = head_y;
    int seg_rad = 10;

    // Draw head.
    al_draw_filled_circle(cur_x, cur_y, (float)seg_rad, al_map_rgb(255, 0, 0));
    int index = 1;

    while (index < snake.get_length()) {
        Direction pos = snake.get_segment_position(index);
        switch (pos) {
            case Direction::north:
                cur_y -= seg_rad * 2;
                break;
            case Direction::south:
                cur_y += seg_rad * 2;
                break;
            case Direction::east:
                cur_x += seg_rad * 2;
                break;
            case Direction::west:
                cur_x -= seg_rad * 2;
                break;
            default:
                break;
        }

        al_draw_filled_circle(cur_x, cur_y, (float)seg_rad, al_map_rgb(0, 255, 0));
        index++;
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

    Snake snake {Direction::east};
    snake.update_head_dir(Direction::north);
    snake.print();
    int head_x = 200;
    int head_y = 200;
    draw_snake(snake, head_x, head_y);
    al_flip_display();


    while (true) {
        al_wait_for_event(event_queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                snake.move();
                snake.print();
                
                /*Just some lines to redraw the snake.*/
                head_y -= 20; // Since head's velocity is North
                al_clear_to_color(al_map_rgb(0, 0, 0));
                draw_snake(snake, head_x, head_y);
                al_flip_display();
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_event_queue_is_empty(event_queue)) {


        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
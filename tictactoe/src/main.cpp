#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Model.h"

const int DISP_WIDTH = 640;
const int DISP_HEIGHT = 480;
const int BOARD_LINE_LENGTH = 250;
const int BOARD_X = (DISP_WIDTH - BOARD_LINE_LENGTH) / 2; // top-left corner of board (x-coord)
const int BOARD_Y = (DISP_HEIGHT - BOARD_LINE_LENGTH) / 2; // top-left corner of board (y-coord)
const int SLOT_SIDE_LENGTH = 250 / 3; // side length of each of the nine slots
const ALLEGRO_COLOR X_SYMB_COLOR = al_map_rgb(0, 80, 255);
const ALLEGRO_COLOR O_SYMB_COLOR = al_map_rgb(255, 255, 255);
const int FONT_CENTER_X = DISP_WIDTH / 2;
const int FONT_CENTER_Y = 30;

// parameters indicate bounding box
void draw_symbol_X(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color) {
    al_draw_line(x1, y1, x2, y2, color, 2);
    al_draw_line(x1, y2, x2, y1, color, 2);
}

// parameters indicate bounding box
void draw_symbol_O(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color) {
    al_draw_ellipse(x1 + ((x2 - x1) / 2), 
                    y1 + (abs(y2 - y1) / 2),
                    (x2 - x1) / 2,
                    abs(y2 - y1) / 2,
                    color,
                    2);
}

void draw_board_symbols(Model& board_model) {
    for (int r = 0; r < board_model.get_board_size(); r++) {
        for (int c = 0; c < board_model.get_board_size(); c++) {
            char symb = board_model.get_symbol(r, c);
            if (symb != ' ')
            {
                int x1 = BOARD_X + c * BOARD_LINE_LENGTH / 3 + 10; // + 10 for padding
                int x2 = BOARD_X + (c + 1) * BOARD_LINE_LENGTH / 3 - 10; // - 10 for padding
                int y1 = BOARD_Y + r * BOARD_LINE_LENGTH / 3 + 10;
                int y2 = BOARD_Y + (r + 1) * BOARD_LINE_LENGTH / 3 - 10;

                if (symb == 'X')
                    draw_symbol_X(x1, y1, x2, y2, X_SYMB_COLOR);
                else if (symb == 'O')
                    draw_symbol_O(x1, y1, x2, y2, O_SYMB_COLOR);
            }
        }
    }
}

// Determine what slot (row, column) the given (x, y) coordinate is in.
// Returns (-1, -1) if the (x, y) coordinate is in no slot.
std::pair<int, int> get_slot_from_xy(int x, int y) {
    // Check if (x,y) is outside the board.
    if (x <= BOARD_X || x >= BOARD_X + BOARD_LINE_LENGTH ||
        y <= BOARD_Y || y >= BOARD_Y + BOARD_LINE_LENGTH)
        return {-1, -1};

    // Check if (x,y) falls directly on a board line.
    if (x == BOARD_X + BOARD_LINE_LENGTH / 3 
        || x == BOARD_X + (2 * BOARD_LINE_LENGTH / 3) 
        || y == BOARD_Y + BOARD_LINE_LENGTH / 3 
        || y == BOARD_Y + (2 * BOARD_LINE_LENGTH / 3))
        return {-1, -1};
    
    
    int row { -1 };
    int col { -1 };

    // Determine row
    if (y > BOARD_Y && y < BOARD_Y + BOARD_LINE_LENGTH / 3)
        row = 0;
    else if (y > BOARD_Y + BOARD_LINE_LENGTH / 3 && y < BOARD_Y + (2 * BOARD_LINE_LENGTH / 3))
        row = 1;
    else //therefore,  y > BOARD_Y + (2 * BOARD_LINE_LENGTH / 3) && y < BOARD_Y + BOARD_LINE_LENGTH
        row = 2;

    // Determine column
    if (x > BOARD_X && x < BOARD_X + BOARD_LINE_LENGTH / 3)
        col = 0;
    else if (x > BOARD_X + BOARD_LINE_LENGTH / 3 && x < BOARD_X + (2 * BOARD_LINE_LENGTH / 3))
        col = 1;
    else //therefore,  x > BOARD_X + (2 * BOARD_LINE_LENGTH / 3) && x < BOARD_X + BOARD_LINE_LENGTH
        col = 2;

    return {row, col};
}



int main() {
    al_init();
    //al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    ALLEGRO_DISPLAY* display = al_create_display(DISP_WIDTH, DISP_HEIGHT);
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb_f(0, 0, 0));
    al_flip_display();

    Model board_model {};

    int x_mouse {};
    int y_mouse {};

    std::pair<int, int> selected_slot {-1, -1};

    ALLEGRO_FONT* font = al_load_ttf_font("assets/Arial.ttf", 40, 0);
    if (font) {std::cout << "Font success\n";}

    ALLEGRO_EVENT event {};
    bool done = false;
    bool redraw = false;
    bool has_winner = false;
    bool is_finished = false;
    al_start_timer(timer);
    while(true) {
        al_wait_for_event(event_queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                x_mouse = event.mouse.x;
                y_mouse = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                selected_slot = get_slot_from_xy(x_mouse, y_mouse);
                std::cout << "Slot: [" << selected_slot.first << "," << selected_slot.second << "]\n"; 
                board_model.play(selected_slot.first, selected_slot.second);
                if (board_model.has_winner()) {
                    has_winner = true;
                    is_finished = true;
                    std::cout << "Winner!\n";
                }
                else if (board_model.board_is_full()) {
                    is_finished = true;
                }
                break;
        }

        if (done)
            break;

        if (redraw && al_event_queue_is_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0,0,0));

            // left border:
            /* al_draw_line(BOARD_X, BOARD_Y, BOARD_X, BOARD_Y + BOARD_LINE_LENGTH, 
                            al_map_rgb(100, 0, 0), 1); */
            // bottom border:
            /* al_draw_line(BOARD_X, BOARD_Y + BOARD_LINE_LENGTH, 
                            BOARD_X + BOARD_LINE_LENGTH, BOARD_Y + BOARD_LINE_LENGTH,
                            al_map_rgb(100, 0, 0), 1); */

            // left vertical line:
            al_draw_line(BOARD_X + (BOARD_LINE_LENGTH / 3), BOARD_Y,
                            BOARD_X + (BOARD_LINE_LENGTH / 3) ,BOARD_Y + BOARD_LINE_LENGTH,
                            al_map_rgb(255, 0, 0), 1);

            // right vertical line:
            al_draw_line(BOARD_X + (2 * BOARD_LINE_LENGTH / 3), BOARD_Y,
                            BOARD_X + (2 * BOARD_LINE_LENGTH / 3) ,BOARD_Y + BOARD_LINE_LENGTH,
                            al_map_rgb(255, 0, 0), 1);

            // first horizontal line:
            al_draw_line(BOARD_X, BOARD_Y + (BOARD_LINE_LENGTH / 3),
                            BOARD_X + BOARD_LINE_LENGTH ,BOARD_Y + (BOARD_LINE_LENGTH / 3),
                            al_map_rgb(255, 0, 0), 1);

            // second horizontal line:
            al_draw_line(BOARD_X, BOARD_Y + (2 * BOARD_LINE_LENGTH / 3),
                            BOARD_X + BOARD_LINE_LENGTH ,BOARD_Y + (2 * BOARD_LINE_LENGTH / 3),
                            al_map_rgb(255, 0, 0), 1);


            //std::cout << std::to_string(x_mouse) << ", " << std::to_string(y_mouse) << "\n";
            std::string message {"NO"};

            if (board_model.has_winner()) {
                std::string winner = std::string(1, board_model.get_winner());
                message = winner + " Wins";
            }

            else if (board_model.board_is_full()) {
                message = "No Winner";
            }

            else {
                std::string player = std::string(1, board_model.get_cur_player());
                message = player + " Turn";
            }
            
            al_draw_text(font, al_map_rgb(255, 255, 255), 640/2, 50, ALLEGRO_ALIGN_CENTER, message.c_str());
            draw_board_symbols(board_model);
            al_flip_display();
            redraw = false;
            }
        }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}

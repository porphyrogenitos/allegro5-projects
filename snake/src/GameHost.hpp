#pragma once

#include <iostream>
#include <utility>
#include <unordered_set>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Constants.hpp"
#include "State.hpp"

class GameClass;



struct Player {
    int points {};
};

// TODO: This is going to host (i.e. be the container for) levels and menus.
// Game.cpp should be converted to a class that can be instantiated here.
// GameHost can also keep track of players.

class GameHost {
private:
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT event {};
    State state;
    Player player1;

    unsigned char key[ALLEGRO_KEY_MAX];

    void init();

    void deinit();
public:
    GameHost();

    ALLEGRO_EVENT* get_event_ptr();

    ALLEGRO_DISPLAY* get_display_ptr();

    ALLEGRO_TIMER* get_timer_ptr();

    ALLEGRO_EVENT_QUEUE* get_event_queue_ptr();

    unsigned char* get_key_array();

    void run();

    void change_state(State next_state);

    void state_ended();

};

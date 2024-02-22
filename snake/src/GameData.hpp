/*
    TODO

    All common game data will be stored in a GameData object, which can then be passed to State objects.
    This is so that GameHost (i.e. the application) doesn't act as storage -- we move all game storage to a separate object.

    The main point of this is to allow data to move between States.
    Game data stored here will not include StateManager or StateFactory, Snake, or UI components.

    Data found here will include:
        -Player curent score
        -Screen cap (could be useful to pass from PlayState to GameOverState)
        -Settings
            -Keyboard controls
        -(TODO) Current level
*/

#pragma once

#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
struct GameData {
    std::string player_name {"Player 1"};
    int current_score {0};
    ALLEGRO_BITMAP *screen_cap {};

    // TODO: font gets destroyed in GameHost::deinit(). Is that a good idea?
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", 25, 0)};
};
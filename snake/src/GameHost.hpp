#pragma once

#include <iostream>
#include <utility>
#include <unordered_set>
#include <memory>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Constants.hpp"
#include "Platform.hpp"

class GameClass;
class State;
class StateFactory;
class StateManager;


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
    
    std::shared_ptr<StateFactory> state_factory;
    std::shared_ptr<StateManager> state_manager;
    std::shared_ptr<State> curr_state;

    std::unique_ptr<Platform> platform;


    Player player1;

    void init();

    void deinit();
public:
    GameHost();

    void tick();

    void draw();
};

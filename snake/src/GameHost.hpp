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
#include "GameData.hpp"

class GameClass;
class State;
class StateFactory;
class StateManager;


struct Player {
    int points {};
};

/**
 * @brief The overall game application.
 * 
 */
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
    std::unique_ptr<GameData> game_data;


    Player player1;

    void init();

    void deinit();
public:
    GameHost();

    void tick();

    void draw();
};

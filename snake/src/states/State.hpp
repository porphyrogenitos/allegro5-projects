#pragma once

#include <string>
#include <memory>
#include "../Platform.hpp"
#include "../GameData.hpp"

enum class StateID {
    MENU,
    PLAY,
    GAME_OVER,
};

/**
 * @brief Base class for game states. A state can update itself, detect input, and
 * draw to the display.
 * 
 * Each state is associated with a particular StateID.
 * 
 * Each state can decide what it's next state should be.
 * If the next state is not updated, next_state == curr_state.
 * 
 * TODO: Is "Scene" a more appropriate word than "State"?
 */
class State {
protected:
    StateID curr_state;
    StateID next_state;
    Platform* platform;
    GameData* game_data;

public:
    State(StateID curr_state, Platform* platform, GameData* game_data);
    virtual void tick() = 0;
    virtual void draw() = 0;
    StateID get_next_state();
    StateID get_id();
    virtual ~State() = default;
};
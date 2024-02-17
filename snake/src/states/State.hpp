#pragma once

#include <string>
#include <memory>
#include "../Platform.hpp"

// TODO: Change to "StateID"
enum class StateID {
    MENU,
    PLAY,
    GAME_OVER,
};

//TODO: Is "Scene" a more appropriate word than "State"?
class State {
protected:
    StateID curr_state;
    StateID next_state;
    Platform* platform;

public:
    State(StateID curr_state, Platform* platform);
    virtual void tick() = 0;
    virtual void draw() = 0;
    StateID get_next_state();
    StateID get_id();
    virtual ~State() = default;
};
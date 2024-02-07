#pragma once

#include <string>
#include <memory>
#include "../Platform.hpp"

enum class StateEnum {
    MENU,
    PLAY,
    GAME_OVER,
};

//TODO: Is "Scene" a more appropriate word than "State"?
class State {
protected:
    StateEnum curr_state;
    StateEnum next_state;
    Platform* platform;

public:
    State(StateEnum curr_state, Platform* platform);
    virtual void tick() = 0;
    virtual void draw() = 0;
    StateEnum get_next_state();
    virtual ~State() = default;
};
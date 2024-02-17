#pragma once

#include <iostream>
#include <memory>
#include "State.hpp"
#include "../GameClass.hpp"
#include "../Platform.hpp"

class PlayState : public State {
private:
    std::unique_ptr<GameClass> gameclass;
public:
    PlayState(StateEnum curr_state, Platform* platform);
    void tick();
    void draw();
    void set_next_state(StateEnum next_state);
};
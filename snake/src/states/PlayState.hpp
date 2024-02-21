#pragma once

#include <iostream>
#include <memory>
#include "State.hpp"
#include "../GameClass.hpp"
#include "../Platform.hpp"
#include "../Label.hpp"

class PlayState : public State {
private:
    std::unique_ptr<GameClass> gameclass;
    std::unique_ptr<Label> score_label;
public:
    PlayState(StateID curr_state, Platform* platform, GameData* game_data);
    void tick();
    void draw();
    void set_next_state(StateID next_state);
};
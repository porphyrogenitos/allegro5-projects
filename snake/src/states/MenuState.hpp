#pragma once

#include <iostream>
#include <memory>
#include "State.hpp"
#include "../Platform.hpp"
#include "../ButtonGroup.hpp"

class MenuState : public State{
    std::unique_ptr<ButtonGroup> menu;
public:
    MenuState(StateID curr_state, Platform* platform);
    void tick();
    void draw();
    void set_next_state(StateID st_enum);
    //void MenuState::set_state_to_play();
};
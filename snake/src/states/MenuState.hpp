#pragma once

#include <iostream>
#include <memory>
#include "State.hpp"
#include "../Platform.hpp"
#include "../GameData.hpp"
#include "../ButtonGroup.hpp"

class MenuState : public State{
    std::unique_ptr<ButtonGroup> menu_buttons;
public:
    MenuState(StateID curr_state, Platform* platform, GameData* game_data);
    void tick();
    void draw();
    void set_next_state(StateID st_enum);
    //void MenuState::set_state_to_play();
};
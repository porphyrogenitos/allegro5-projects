#pragma once

#include <iostream>
#include "State.hpp"
#include "../Menu.hpp"

class GameHost;

class MenuState : public State{
    std::unique_ptr<Menu> menu;
public:
    MenuState(Gamehost* gamehost);
    void tick();
    void draw();
};
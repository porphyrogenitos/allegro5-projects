#pragma once

#include <iostream>
#include <memory>
#include "../Constants.hpp"
#include "State.hpp"
#include "../Menu.hpp"

class GameHost;

class MenuState : public State{
    std::unique_ptr<Menu> menu;
public:
    MenuState(GameHost* gamehost);
    void tick();
    void draw();
};
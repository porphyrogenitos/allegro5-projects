#pragma once

#include <iostream>
#include <memory>
#include "State.hpp"
#include "../GameClass.hpp"

class GameHost;

class PlayState : public State {
private:
    std::unique_ptr<GameClass> gameclass;
public:
    PlayState(GameHost* gamehost);
    void tick();
    void draw();

};
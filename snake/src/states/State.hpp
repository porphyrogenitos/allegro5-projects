#pragma once

#include <string>
class GameHost;

enum class StateEnum {
    MENU,
    PLAY,
    PAUSED,
    GAME_OVER,
};

//TODO: Is "Scene" a more appropriate word than "State"?
class State {
protected:
    GameHost* gamehost;
public:
    State(GameHost* gamehost);
    virtual void tick() = 0;
    virtual void draw() = 0;
    virtual ~State() = default;
};
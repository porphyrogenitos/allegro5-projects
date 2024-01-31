#pragma once

#include <memory>
#include "states/State.hpp"
#include "states/MenuState.hpp"
#include "states/PlayState.hpp"

class GameHost;

class StateFactory {
public:
    virtual std::shared_ptr<State> create(StateEnum st_enum, GameHost* gamehost);
    virtual ~StateFactory() = default;
};
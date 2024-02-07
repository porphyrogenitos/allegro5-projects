#pragma once

#include <memory>
#include "Platform.hpp"
#include "states/State.hpp"
#include "states/MenuState.hpp"
#include "states/PlayState.hpp"

class StateManager;

class StateFactory {
public:
    virtual std::shared_ptr<State> create(StateEnum st_enum, Platform* platform);
    virtual ~StateFactory() = default;
};
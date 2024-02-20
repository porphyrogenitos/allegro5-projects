#pragma once

#include <memory>
#include "Platform.hpp"
#include "GameData.hpp"
#include "states/State.hpp"
#include "states/MenuState.hpp"
#include "states/PlayState.hpp"
#include "states/GameOverState.hpp"

class StateManager;

class StateFactory {
public:
    virtual std::unique_ptr<State> create(StateID st_enum, Platform* platform, GameData* game_data);
    virtual ~StateFactory() = default;
};
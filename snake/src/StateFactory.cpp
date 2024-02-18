#include "StateFactory.hpp"
#include "StateManager.hpp"


std::unique_ptr<State> StateFactory::create(StateID st_enum, Platform* platform) {
    switch (st_enum)
    {
    case StateID::MENU:
        return std::make_unique<MenuState>(st_enum, platform);
    case StateID::PLAY:
        return std::make_unique<PlayState>(st_enum, platform);
    case StateID::GAME_OVER:
        return std::make_unique<GameOverState>(st_enum, platform);
    
    default:
        return nullptr;
    }
}
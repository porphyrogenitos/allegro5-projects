#include "StateFactory.hpp"
#include "StateManager.hpp"


std::shared_ptr<State> StateFactory::create(StateEnum st_enum, Platform* platform) {
    switch (st_enum)
    {
    case StateEnum::MENU:
        return std::make_shared<MenuState>(st_enum, platform);
    case StateEnum::PLAY:
        return std::make_shared<PlayState>(st_enum, platform);
    
    default:
        return nullptr;
    }
}
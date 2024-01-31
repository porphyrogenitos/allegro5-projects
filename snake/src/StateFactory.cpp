#include "StateFactory.hpp"
#include "GameHost.hpp"

std::shared_ptr<State> StateFactory::create(StateEnum st_enum, GameHost* gamehost) {
    switch (st_enum)
    {
    case StateEnum::MENU:
        return std::make_shared<MenuState>(gamehost);
    case StateEnum::PLAY:
        return std::make_shared<PlayState>(gamehost);
    
    default:
        return nullptr;
    }
}
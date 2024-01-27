#include "State.hpp"

std::string state_to_string(State state) {
    switch (state)
    {
    case State::GAME_OVER:
        return "GAME_OVER";

    case State::LEVEL:
        return "LEVEL";
    
    case State::MENU:
        return "MENU";
    
    default:
        return "";
    }
}
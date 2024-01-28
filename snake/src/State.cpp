#include "State.hpp"

std::string state_to_string(State state) {
    switch (state)
    {
    case State::GAME_OVER:
        return "GAME_OVER";

    case State::PLAY:
        return "PLAY";
    
    case State::MENU:
        return "MENU";
    
    default:
        return "";
    }
}
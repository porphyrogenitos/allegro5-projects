#include <string>

enum class State {
    MENU,
    LEVEL,
    GAME_OVER,
};

std::string state_to_string(State state);
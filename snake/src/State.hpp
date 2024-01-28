#include <string>

enum class State {
    MENU,
    PLAY,
    PAUSED,
    GAME_OVER,
};

std::string state_to_string(State state);
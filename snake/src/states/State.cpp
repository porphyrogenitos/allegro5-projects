#include "State.hpp"

State::State(StateID curr_state, Platform* platform, GameData* game_data) {
    this->curr_state = curr_state;
    next_state = curr_state;

    this->platform = platform;
    this->game_data = game_data;
};

StateID State::get_next_state() {
    return next_state;
}

StateID State::get_id() {
    return curr_state;
}
#include "State.hpp"

State::State(StateID curr_state, Platform* platform) {
    this->curr_state = curr_state;
    next_state = curr_state;

    this->platform = platform;
};

StateID State::get_next_state() {
    return next_state;
}

StateID State::get_id() {
    return curr_state;
}
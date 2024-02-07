#include "State.hpp"

State::State(StateEnum curr_state, Platform* platform) {
    this->curr_state = curr_state;
    next_state = curr_state;

    this->platform = platform;
};

StateEnum State::get_next_state() {
    return next_state;
}
#include "StateManager.hpp"
#include "StateFactory.hpp"

StateManager::StateManager(StateEnum initial_state, Platform* platform, std::shared_ptr<StateFactory> state_factory){
    this->platform = platform;
    this->state_factory = state_factory;
    curr_state = state_factory->create(initial_state, this->platform);
}

void StateManager::set_state(StateEnum next_state){
    curr_state.reset();
    curr_state = state_factory->create(next_state, this->platform);
}

std::shared_ptr<State> StateManager::get_curr_state(){
    return curr_state;
}

void StateManager::update_state() {
    if (curr_state->get_next_state() != curr_state->get_id()) {
        set_state(curr_state->get_next_state());
    }
}
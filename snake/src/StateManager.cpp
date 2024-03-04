#include "StateManager.hpp"
#include "StateFactory.hpp"

/**
 * @brief Controls the current game State.
 * 
 */


/**
 * @brief StateManager constructor
 * 
 * @param initial_state StateID of the initial state
 * @param platform 
 * @param game_data 
 * @param state_factory Reference to the StateFactory object
 */
StateManager::StateManager(StateID initial_state, Platform* platform, GameData* game_data, StateFactory* state_factory){
    this->platform = platform;
    this->state_factory = state_factory;
    this->game_data = game_data;
    curr_state = state_factory->create(initial_state, this->platform, this->game_data);
}

void StateManager::set_state(StateID next_state){
    curr_state.reset();
    curr_state = state_factory->create(next_state, this->platform, this->game_data);
}

State* StateManager::get_curr_state(){
    return curr_state.get();
}

/**
 * @brief Checks the current state to see if we need to change to a new state.
 * 
 */
void StateManager::update_state() {
    if (curr_state->get_next_state() != curr_state->get_id()) {
        set_state(curr_state->get_next_state());
    }
}
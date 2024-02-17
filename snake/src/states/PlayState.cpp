#include "PlayState.hpp"

PlayState::PlayState(StateEnum curr_state, Platform* platform) : State(curr_state, platform) {
    // TODO: Instead of passing GameHost to GameClass, pass ref to KeyboardManager.
    gameclass = std::make_unique<GameClass>(platform, 
                                            std::bind(&PlayState::set_next_state, this, StateEnum::MENU));
} 

void PlayState::tick() {
    gameclass->tick();
}

void PlayState::draw() {
    gameclass->draw();
}

void PlayState::set_next_state(StateEnum next_state) {
    this->next_state = next_state;

}
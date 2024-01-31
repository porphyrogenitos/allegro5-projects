#include "PlayState.hpp"

PlayState::PlayState(GameHost* gamehost) : State(gamehost) {
    gameclass = std::make_unique<GameClass>(gamehost);
}

void PlayState::tick() {
    std::cout << "PlayState tick!" << std::endl;
    gameclass->tick();
    
}

void PlayState::draw() {
    gameclass->draw();
}
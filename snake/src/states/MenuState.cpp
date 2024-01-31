#include "MenuState.hpp"
#include "../GameHost.hpp"

MenuState::MenuState(GameHost* gamehost) : State(gamehost) {
    menu = std::make_unique<Menu>(gamehost, 0, 0, DISP_WIDTH, DISP_HEIGHT);
}

void MenuState::tick() {
    menu->tick();
}

void MenuState::draw() {
    menu->draw();
}
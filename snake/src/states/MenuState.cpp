#include "MenuState.hpp"
#include "../GameHost.hpp"

MenuState::MenuState(GameHost* gamehost) : State(gamehost) {
    menu = std::make_unique<Menu>(gamehost, 0, 0, DISP_WIDTH, DISP_HEIGHT);
}

void MenuState::tick() {
    std::cout << "MenuState tick!" << std::endl;
    menu->tick();
}

void MenuState::draw() {
    std::cout << "MenuState draw!" << std::endl;
    menu->draw();
}
#include <functional>
#include "MenuState.hpp"
#include "../Constants.hpp"


MenuState::MenuState(StateEnum curr_state, Platform* platform) : State(curr_state, platform) {
    menu = std::make_unique<Menu>(this->platform, 0, 0, DISP_WIDTH, DISP_HEIGHT);


    menu->add_button("PLAY", std::bind(&MenuState::set_next_state, this, StateEnum::PLAY));
    //menu->add_button("CONTROLS", ...);
    //menu->add_button("ABOUT", ...);

}

void MenuState::tick() {
    menu->tick();
}

void MenuState::draw() {
    menu->draw();
}

// Handler for Menu
void MenuState::set_next_state(StateEnum next_state) {
    this->next_state = next_state;
}


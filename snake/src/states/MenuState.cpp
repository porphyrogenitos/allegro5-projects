#include <functional>
#include "MenuState.hpp"
#include "../Constants.hpp"


MenuState::MenuState(StateID curr_state, Platform* platform) : State(curr_state, platform) {
    menu = std::make_unique<ButtonGroup>(this->platform, 0, 0, DISP_WIDTH, DISP_HEIGHT);


    menu->add_button("PLAY", std::bind(&MenuState::set_next_state, this, StateID::PLAY));
    //menu->add_button("CONTROLS", ...);
    //menu->add_button("ABOUT", ...);
    //menu->add_button("EXIT", ...);

}

void MenuState::tick() {
    menu->tick();
}

void MenuState::draw() {
    menu->draw();
}

// Handler for ButtonGroup
void MenuState::set_next_state(StateID next_state) {
    this->next_state = next_state;
}


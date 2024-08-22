#include <iostream>
#include <functional>
#include "MenuState.hpp"
#include "../Constants.hpp"

void printControls() {
    std::cout << "Controls\n";
}

void printAbout() {
    std::cout << "About\n";
}


MenuState::MenuState(StateID curr_state, Platform* platform, GameData* game_data) : State(curr_state, platform, game_data) {
    menu_buttons = std::make_unique<ButtonGroup>(this->platform, 0, 0, DISP_WIDTH, DISP_HEIGHT);


    menu_buttons->add_button("PLAY", std::bind(&MenuState::set_next_state, this, StateID::PLAY));
    //menu_buttons->add_button("CONTROLS", std::bind(&MenuState::set_next_state, this, StateID::CONTROLS));
    menu_buttons->add_button("CONTROLS", std::bind(&MenuState::set_next_state, this, StateID::CONTROLS));
    menu_buttons->add_button("ABOUT", std::bind(printAbout));
    menu_buttons->add_button("EXIT", std::bind(&MenuState::set_exit, this));

}

void MenuState::set_exit() {
    this->platform->exit = true;
}

void MenuState::tick() {
    menu_buttons->tick();
}

void MenuState::draw() {
    menu_buttons->draw();
}

// Handler for ButtonGroup
void MenuState::set_next_state(StateID next_state) {
    this->next_state = next_state;
}




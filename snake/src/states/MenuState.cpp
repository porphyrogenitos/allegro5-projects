#include <functional>
#include "MenuState.hpp"
#include "../Constants.hpp"


MenuState::MenuState(StateEnum curr_state, Platform* platform) : State(curr_state, platform) {
    menu = std::make_unique<Menu>(this->platform, 0, 0, DISP_WIDTH, DISP_HEIGHT);

    
    
    //TODO: Bind set_next_state(StateEnum::PLAY) to a void no-args function

    menu->add_button("PLAY", std::bind(&MenuState::set_next_state, this, StateEnum::PLAY));
    //menu->add_button("CONTROLS", ...);
    //menu->add_button("ABOUT", ...);

}

void MenuState::tick() {
    if (next_state != curr_state) {
        
    }

    menu->tick();
}

void MenuState::draw() {
    menu->draw();
}

// Handler for Menu
// "Play" button handler would be set to MenuState::set_next_state(StateEnum::PLAY).
void MenuState::set_next_state(StateEnum next_state) {
    this->next_state = next_state;
}


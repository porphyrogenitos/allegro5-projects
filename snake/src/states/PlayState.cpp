#include "PlayState.hpp"

PlayState::PlayState(StateID curr_state, Platform* platform, GameData* game_data) : State(curr_state, platform, game_data) {

    // Right now I'm passing all handler functions via constructor args. This is obviously not very good.
    // TODO: Might be good to replace with Observer pattern.
    gameclass = std::make_unique<GameClass>(platform,
                                            game_data,
                                            std::bind(&PlayState::set_next_state, this, StateID::MENU),
                                            std::bind(&PlayState::set_next_state, this, StateID::GAME_OVER));
    gameclass->set_dimensions(0, TILE_WIDTH * 3, DISP_WIDTH, DISP_HEIGHT - TILE_WIDTH * 3);
} 

void PlayState::tick() {
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_P))
        while (true) {}
    
    gameclass->tick();
}

void PlayState::draw() {
    gameclass->draw();
}

void PlayState::set_next_state(StateID next_state) {
    this->next_state = next_state;

}
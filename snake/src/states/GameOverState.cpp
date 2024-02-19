#include "GameOverState.hpp"


GameOverState::GameOverState(StateID curr_state, Platform* platform) : State(curr_state, platform) {
    
} 

void GameOverState::tick() {
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_ESCAPE)) {
        platform->exit = true;
        return;
    }
    

}

void GameOverState::draw() {
    al_draw_filled_rectangle(0, 0, DISP_WIDTH, DISP_HEIGHT, al_map_rgb(0, 0, 0));
    label.draw();
}
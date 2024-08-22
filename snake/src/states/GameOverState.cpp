#include "GameOverState.hpp"


GameOverState::GameOverState(StateID curr_state, Platform* platform, GameData* game_data) : State(curr_state, platform, game_data) {
    label.set_dimensions(DISP_WIDTH / 2 - 20, // For centering along x (note, 20 = 40 / 2, i.e. half the specified width)
                        DISP_HEIGHT / 2 - 30,
                        40, // width
                        al_get_font_line_height(font) // height
                        );
    label.text = "GAME OVER";
    label.text_color = al_map_rgb(255, 255, 255);
    label.font = game_data->font;
    label.alignment_flag = ALLEGRO_ALIGN_CENTRE;


    score_label.set_dimensions(DISP_WIDTH / 2 - 50, // For centering along x
                                DISP_HEIGHT / 2 + 40 - al_get_font_ascent(font) / 2,
                                100, // width
                                al_get_font_line_height(font) // height
                                );
    score_label.text = "YOUR SCORE: " + std::to_string(game_data->current_score);
    score_label.text_color = al_map_rgb(255, 255, 255);
    score_label.font = game_data->font,
    score_label.alignment_flag = ALLEGRO_ALIGN_CENTRE;
} 

void GameOverState::tick() {
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_ESCAPE)) {
        this->next_state = StateID::MENU;
        return;
    }
}

void GameOverState::draw() {
    al_draw_filled_rectangle(0, 0, DISP_WIDTH, DISP_HEIGHT, al_map_rgb(0, 0, 0));
    label.draw();
    score_label.draw();
}
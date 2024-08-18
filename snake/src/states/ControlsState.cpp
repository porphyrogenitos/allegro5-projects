#include "ControlsState.hpp"

ControlsState::ControlsState(StateID curr_state, Platform* platform, GameData* game_data) : State(curr_state, platform, game_data) {
    label.set_dimensions(DISP_WIDTH / 2 - 20, // For centering along x (note, 20 = 40 / 2, i.e. half the specified width)
                        DISP_HEIGHT / 2 - 30,
                        40, // width
                        al_get_font_line_height(font) // height
                        );
    label.text = "Controls";
    label.text_color = al_map_rgb(255, 255, 255);
    label.font = game_data->font;
    label.alignment_flag = ALLEGRO_ALIGN_CENTRE;
}

void ControlsState::tick() {
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_ESCAPE)) {
        this->next_state = StateID::MENU;
        return;
    }
}

// TODO
void ControlsState::draw() {
    al_draw_filled_rectangle(0, 0, DISP_WIDTH, DISP_HEIGHT, al_map_rgb(0, 0, 0));
    label.draw();
}
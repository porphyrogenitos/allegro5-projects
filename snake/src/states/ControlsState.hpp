#pragma once

#include <memory>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../Constants.hpp"
#include "../Platform.hpp"
#include "State.hpp"
#include "../GameData.hpp"
#include "../Label.hpp"


class ControlsState : public State{

private:
    int font_size = 25;
    //TODO: Get font from GameData instead.
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", font_size, 0)};
    ALLEGRO_COLOR background {al_map_rgba(0, 0, 0, 0)};
    Label label {};

public:
    ControlsState(StateID curr_state, Platform* platform, GameData* game_data);
    void tick();
    void draw();
};
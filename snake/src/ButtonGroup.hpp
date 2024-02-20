#pragma once

#include <array>
#include <vector>
#include <functional>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Constants.hpp"
#include "Button.hpp"
#include "Platform.hpp"

class ButtonGroup {

    //TODO: I want it to automatically calculate the layout of 3 buttons based on
    // a string array with three slots for text.

private:
    int x;
    int y;
    int width;
    int height;
    int font_size = 25; //TODO: We might not want to hardcode this
    Platform* platform;
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", font_size, 0)};
    ALLEGRO_COLOR background {al_map_rgba(1, 50, 32, 0)}; // Dark green
    bool is_transparent {false};

    std::vector<Button> menu_buttons;
    
    /* = {Button {"PLAY", font},
                            Button {"CONTROLS", font},
                            Button {"ABOUT", font},
                            Button {"Do Not Click", font}};
    */
    int hovered_item = 0;

public:
    ButtonGroup(Platform* platform, int x, int y, int width, int height);
    ~ButtonGroup();

    void set_background_transparent(bool set);
    void add_button(std::string text, std::function<void()> handler);
    void resize_menu_buttons();
    void tick();
    void draw();
};
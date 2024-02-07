#pragma once

#include <array>
#include <functional>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Constants.hpp"
#include "MenuButton.hpp"
#include "Platform.hpp"

class Menu {

    //TODO: Figuring out how MenuButton should relate to Menu.
    // I want it to automatically calculate the layout of 3 menu buttons based on
    // a string array with three slots for text.

private:
    int x;
    int y;
    int width;
    int height;
    int font_size = 25; //TODO: We might not want to hardcode this
    Platform* platform;
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", font_size, 0)};
    ALLEGRO_COLOR background {al_map_rgb(1, 50, 32)}; // Dark green

    std::array<MenuButton, 4> menu_buttons = {MenuButton {"PLAY", font},
                            MenuButton {"CONTROLS", font},
                            MenuButton {"ABOUT", font},
                            MenuButton {"Do Not Click", font}};
    int hovered_item = 0;

public:
    Menu(Platform* platform, int x, int y, int width, int height);
    ~Menu();

    void add_button(std::string text, std::function<void()> handler);
    void resize_menu_buttons();
    void tick();
    void draw();
};
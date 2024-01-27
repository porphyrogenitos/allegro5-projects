#pragma once

#include <array>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Constants.hpp"
#include "GameHost.hpp"
#include "MenuItem.hpp"

class Menu {

    //TODO: Figuring out how MenuItem should relate to Menu.
    // I want it to automatically calculate the layout of 3 menu buttons based on
    // a string array with three slots for text.

    // TODO: Add more MenuItems to Menu

private:
    int x;
    int y;
    int width;
    int height;
    int font_size = 25; //TODO: We might not want to hardcode this
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_DISPLAY* display;
    unsigned char* key;
    GameHost* gamehost;
    ALLEGRO_FONT* font {al_load_ttf_font("assets/Consolas.ttf", font_size, 0)};
    ALLEGRO_COLOR background {al_map_rgb(1, 50, 32)}; // Dark green

    std::array<MenuItem, 4> menu_items = {MenuItem {"Hello world", font},
                            MenuItem {"Goodbye world", font},
                            MenuItem {"WFE", font},
                            MenuItem {"Last item", font}};
    int hovered_item = 0;

public:
    Menu(GameHost* gamehost, int x, int y, int width, int height);
    ~Menu();

    void resize_menuitems();
    void draw();
    void run();

};
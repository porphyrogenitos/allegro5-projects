#pragma once

#include <string>
#include <functional>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

struct MenuButton {
public:
    int x;
    int y;
    int width;
    int height;
    std::string text;
    bool hovering;
    ALLEGRO_FONT* font;
    std::function<void()> handler {};

    MenuButton(int x, int y, int width, int height, std::string text, ALLEGRO_FONT* font);
    MenuButton(std::string text, ALLEGRO_FONT* font);


    void draw();

    void select();

private:
    int get_center_x();
    int get_center_y();
};
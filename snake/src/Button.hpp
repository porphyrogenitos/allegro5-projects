#pragma once

#include <string>
#include <functional>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

/**
 * @brief UI button with action handler.
 * 
 */
struct Button {
public:
    int x;
    int y;
    int width;
    int height;
    std::string text;
    bool hovering;
    ALLEGRO_FONT* font;
    std::function<void()> handler {};

    Button(int x, int y, int width, int height, std::string text, ALLEGRO_FONT* font);
    Button(std::string text, ALLEGRO_FONT* font);
    Button(std::string text, ALLEGRO_FONT* font, std::function<void()> handler);

    /**
     * @brief Draws text within rectangle. Color of text and background depends on whether
     * button is hovered over.
     * 
     */
    void draw();

    /**
     * @brief Calls action handler.
     * 
     */
    void select();

private:
    /**
     * @brief Gets the center x-coordinate of the Button.
     * 
     * @return int 
     */
    int get_center_x();

    /**
     * @brief Gets the center y-coordinate of the Button.
     * 
     * @return int 
     */
    int get_center_y();
};
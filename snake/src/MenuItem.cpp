#include "MenuItem.hpp"

// Constructor
MenuItem::MenuItem(int x, int y, int width, int height, std::string text, ALLEGRO_FONT* font) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->font = font;
    hovering = false;
}

// Constructor
MenuItem::MenuItem(std::string text, ALLEGRO_FONT* font) : 
    MenuItem(0, 0, 0, 0, text, font) {}

//Draws white text against a black rectangle when unhovered, and the reverse when hovered.
void MenuItem::draw() {

        ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
        ALLEGRO_COLOR background_color = al_map_rgb(50, 50, 50);

    if (hovering) {
        text_color = al_map_rgb(0, 0, 0);
        background_color = al_map_rgb(255, 255, 255);
    }

    al_draw_filled_rectangle(x, y, x + width, y + height, background_color);
    al_draw_text(font, text_color, get_center_x(), get_center_y(), ALLEGRO_ALIGN_CENTRE, text.c_str());
}

void MenuItem::select() {
    handler();
}

// Gets the center x-coordinate of the MenuItem.
int MenuItem::get_center_x() {
    return x + (width / 2);
}

// Gets the center y-coordinate of the MenuItem.
int MenuItem::get_center_y() {
    return y + (height / 2) - (al_get_font_line_height(font) / 2);
}
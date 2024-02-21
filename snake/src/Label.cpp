#include "Label.hpp"

Label::Label(int x, int y, int width, int height, std::string text, ALLEGRO_COLOR text_color, ALLEGRO_FONT* font, int alignment_flag) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->text_color = text_color;
    this->font = font;
    this->alignment_flag = alignment_flag;
}

void Label::draw() {
    switch (alignment_flag)
    {
    case ALLEGRO_ALIGN_CENTRE:
        al_draw_text(font, text_color, get_center_x(), get_center_y(), ALLEGRO_ALIGN_CENTRE, text.c_str());
        break;
    case ALLEGRO_ALIGN_LEFT:
        al_draw_text(font, text_color, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
        break;
    case ALLEGRO_ALIGN_RIGHT:
        al_draw_text(font, text_color, x + width, y + height, ALLEGRO_ALIGN_RIGHT, text.c_str());
    
    default:
        break;
    }
}

// Gets the center x-coordinate of the Label.
int Label::get_center_x() {
    return x + (width / 2);
}

// Gets the center y-coordinate of the Label.
int Label::get_center_y() {
    return y + (height / 2) - (al_get_font_line_height(font) / 2);
}
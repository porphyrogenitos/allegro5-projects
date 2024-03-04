#pragma once

#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/**
 * @brief GUI label for displaying text.
 * 
 */
struct Label {
public:
    std::string text;
    int x {};
    int y {};
    int width {};
    int height {};
    ALLEGRO_FONT* font {};
    ALLEGRO_COLOR text_color {};
    int alignment_flag {};

    Label(int x, int y, int width, int height, std::string text, ALLEGRO_COLOR text_color, ALLEGRO_FONT* font, int alignment_flag);
    Label();

    void set_dimensions(int x, int y, int width, int height);

    void set_dimensions(int width, int height);

    void draw();

private:
    int get_center_x();
    int get_center_y();
};
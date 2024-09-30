#pragma once

#include <allegro5/allegro5.h>
#include "Globals.hpp"

class KeyboardManager {
private:
    unsigned char key[ALLEGRO_KEY_MAX];
public:
    KeyboardManager();
    void tick();
    void key_pressed(int keycode);
    void key_released(int keycode);
    bool key_was_pressed(int keycode);
};

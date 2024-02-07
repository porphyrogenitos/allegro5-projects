#include "KeyboardManager.hpp"

KeyboardManager::KeyboardManager() {
    memset(key, 0, sizeof(key));
}

void KeyboardManager::tick() {
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
        key[i] &= KEY_SEEN;
}

void KeyboardManager::key_pressed(int keycode) {
    key[keycode] = KEY_SEEN | KEY_RELEASED;
}

void KeyboardManager::key_released(int keycode) {
    key[keycode] &= KEY_RELEASED;
}

bool KeyboardManager::key_was_pressed(int keycode) {
    return key[keycode];
}
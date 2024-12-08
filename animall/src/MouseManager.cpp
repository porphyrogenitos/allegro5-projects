#include "MouseManager.hpp"

//TODO: How to set this up?

MouseManager::MouseManager() {}

void MouseManager::mouse_lbutton_down() {
  lbutton = true;
}

bool MouseManager::mouse_lbutton_is_down() {
  return lbutton;
}
void MouseManager::mouse_lbutton_release() {
  lbutton = false;
}

void MouseManager::move_mouse(int new_x, int new_y) {
  mouse_x = new_x;
  mouse_y = new_y;
  mouse_moved = true;
}

bool MouseManager::was_moved() {
  return moved;
}

void MouseManager::end_move() {
  mouse_moved = false;
}

int get_mouse_x() {
  return mouse_x;
}

int get_mouse_y() {
  return mouse_y;
}


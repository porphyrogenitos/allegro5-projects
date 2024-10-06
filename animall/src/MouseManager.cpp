#include "MouseManager.hpp"

MouseManager::MouseManager() {}

void MouseManager::tick() {
  //TODO (not sure this function is needed)
}

void MouseManager::mouse_lbutton_down() {
  lbutton = true;
}

void MouseManager::mouse_lbutton_release() {
  lbutton = false;
}

void MouseManager::mouse_moved(int new_x, int new_y) {
  mouse_x = new_x;
  mouse_y = new_y;
}

int get_mouse_x() {
  return mouse_x;
}

int get_mouse_y() {
  return mouse_y;
}


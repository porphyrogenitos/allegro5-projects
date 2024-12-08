#pragma once

#include <allegro5/allegro5.h>
#include "Globals.hpp"

class MouseManager {
private:
  int mouse_x {}; //x-coordinate in pixels
  int mouse_y {}; //y-coordinate in pixels
  bool lbutton = false;
  bool moved = false;
    
public:
  MouseManager();
  void mouse_lbutton_down();
  bool mouse_lbutton_is_down();
  void mouse_lbutton_release();
  void move_mouse(int new_x, int new_y);
  bool was_moved();
  int get_mouse_x();
  int get_mouse_y();
};

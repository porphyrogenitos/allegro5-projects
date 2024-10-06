#pragma once

#include <allegro5/allegro5.h>
#include "Globals.hpp"

class MouseManager {
private:
  int mouse_x {}; //x-coordinate in pixels
  int mouse_y {}; //y-coordinate in pixels
  bool lbutton = false;
    
public:
  MouseManager();
  void tick();
  void mouse_lbutton_click();
  void mouse_lbutton_down();
  void mouse_lbutton_release();
  void mouse_moved(int new_x, int new_y);
  int get_mouse_x();
  int get_mouse_y();
};

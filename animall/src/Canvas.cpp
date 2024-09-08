#include <allegro5/allegro5.h>
#include "Canvas.hpp"

Canvas::Canvas(int x, int y, int width, int height, Frame* frame) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  current_frame = frame;
  bit_width = width / frame->get_width();
}

Canvas::Canvas(Frame* frame) {
  current_frame = frame;
}

void Canvas::set_width(int w) {
  width = w;
}

void Canvas::set_height(int h) {
  height = h;
}

void Canvas::set_pos_on_screen(int x, int y) {
  this->x = x;
  this->y = y;
}

void Canvas::set_frame(Frame* new_frame) {
  current_frame = new_frame;
}

void Canvas::update_frame(int x, int y, bool val) {
  current_frame->set(x, y, val);
}

// TODO
void Canvas::draw() {

}

void Canvas::set_draw_mode(DrawMode new_mode) {
  draw_mode = new_mode;
}

#include <allegro5/allegro5.h>
#include "Canvas.hpp"

Canvas::Canvas(Pixel tl_pixel, int width, int height, Frame* frame) {
  this->tl_pixel.x = tl_pixel.x;
  this->tl_pixel.y = tl_pixel.y;
  this->width = width;
  this->height = height;
  current_frame = frame;
  bit_pixel_width = width / frame->get_width();
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

void Canvas::set_tl_pixel(const Pixel& pixel) {
  this->tl_pixel.x = pixel.x;
  this->tl_pixel.y = pixel.y;
}

void Canvas::set_frame(Frame* new_frame) {
  current_frame = new_frame;
}

void Canvas::update_frame_bit(const Bit& frame_bit, bool val) {
  current_frame->set(frame_bit, val);
}

Bit Canvas::get_frame_bit_of_pixel(const Pixel& pixel) {
  int x = pixel.x / bit_pixel_width;
  int y = pixel.y / bit_pixel_width;

  return Bit {x, y};
}

// TODO
void Canvas::draw() {

}

void Canvas::set_draw_mode(DrawMode new_mode) {
  draw_mode = new_mode;
}

DrawMode Canvas::get_draw_mode() {
  return draw_mode;
}

bool Canvas::contains_pixel(const Pixel& pixel) {
  return this->tl_pixel.x <= pixel.x && this->tl_pixel.x + this->width > pixel.x
      && this->tl_pixel.y <= pixel.y && this->tl_pixel.y + this->height > pixel.y;
}

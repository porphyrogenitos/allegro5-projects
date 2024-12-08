#include <allegro5/allegro5.h>
#include "Canvas.hpp"

Canvas::Canvas(Platform* platform, Pixel tl_pixel, int width, int height, Frame* frame) {
  this->platform = platform;
  this->tl_pixel.x = tl_pixel.x;
  this->tl_pixel.y = tl_pixel.y;
  this->width = width;
  this->height = height;
  current_frame = frame;
  bit_pixel_width = width / frame->get_width();
  drag = false;
}

Canvas::Canvas(Platform* platform, Frame* frame) {
  this->platform = platform;
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

// Draw filled white rectangle
  al_draw_filled_rectangle(tl_pixel.x, tl_pixel.y, tl_pixel.x + width, tl_pixel.y + height,
			  al_map_rgb(255, 255, 255));

}

void Canvas::tick() {
  //If mouse clicked within canvas, get mouse xy position on canvas and update
  //corresponding Frame bit based on Canvas draw_mode
  //TODO: Need to consider what happens if you click and drag
  if (platform->mouse_manager.moved() {
    if (drag) {
      int x = mouse_manager.get_mouse_x();
      int y = mouse_manager.get_mouse_y();
      if (canvas->contains_pixel(x, y)) {
        switch (canvas->get_draw_mode()) {
	  case DrawMode::PENCIL:
	    Bit frame_bit = get_frame_bit_of_pixel(Pixel {x, y});
	    update_frame_bit(frame_bit, true);
	    break;
	  case DrawMode::ERASER:
	    Bit frame_bit = get_frame_bit_of_pixel(Pixel {x, y});
	    update_frame_bit(frame_bit, false);
	    break;
        }
      }
    }
  }
  
  if (platform->mouse_manager.mouse_lbutton_down()) {
    drag = true;
    int x = mouse_manager.get_mouse_x();
    int y = mouse_manager.get_mouse_y();
    if (canvas->contains_pixel(x, y) {
      switch (canvas->get_draw_mode()) {
	case DrawMode::PENCIL:
	  Bit frame_bit = get_frame_bit_of_pixel(Pixel {x, y});
	  update_frame_bit(frame_bit, true);
	  break;
	case DrawMode::ERASER:
	  Bit frame_bit = get_frame_bit_of_pixel(Pixel {x, y});
	  update_frame_bit(frame_bit, false);
	  break;
      }
    }
  }
  if (platform->mouse_manager.mouse_lbutton_release()) {
    drag = false;
  }
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

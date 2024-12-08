#pragma once

#include <utility>
#include <allegro5/allegro_primitives.h>
#include "Platform.hpp"
#include "Frame.hpp"
#include "DrawMode.hpp"

using Pixel = std::pair<int, int>;

class Canvas {
private:
  Platform* platform;
  Frame* current_frame {};
  DrawMode draw_mode {DrawMode::PENCIL};
  Pixel tl_pixel {}; //top left pixel coordinates
  int width {}; //in pixels (not bits)
  int height {}; // in pixels (not bits)
  int bit_pixel_width {}; // number of pixels wide for 1 bit of the Frame
  bool drag {}; //is the (left) mouse button being held?

public:
  Canvas(Platform* platform, Pixel tl_pixel, int width, int height, Frame* frame);
  Canvas(Platform* platform, Frame* frame);
  void set_width(int w);
  void set_height(int h);
  void set_tl_pixel(const Pixel& pixel);
  void set_frame(Frame* new_frame);
  void update_frame_bit(const Bit& bit, bool val);
  Bit get_frame_bit_of_pixel(const Pixel& pixel);
  void draw();
  void tick();
  void set_draw_mode(DrawMode new_mode);
  DrawMode get_draw_mode();
  bool contains_pixel(const Pixel& pixel);
  
};

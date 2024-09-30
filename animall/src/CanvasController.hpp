#pragma once

#include <memory>
#include "Platform.hpp"
#include "Animation.hpp"
#include <allegro5/allegro5.h>

#include "Canvas.hpp"
#include "Frame.hpp"
#include "Globals.hpp"

//TODO: InputManager of some sort?

class CanvasController {
private:
  Platform* platform;
  std::unique_ptr<Canvas> canvas;
  std::unique_ptr<Animation> animation;
  Frame cur_frame;
  bool is_playing {};

public:
  CanvasController(Platform* platform);
  void draw();
  void tick();
  Bit convert_pixel_to_frame_bit();
  Pixel convert_frame_bit_to_pixel();
  void play();
  void pause();
};

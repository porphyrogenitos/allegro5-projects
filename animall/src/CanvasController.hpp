#pragma once

#include <memory>
#include <allegro5/allegro5.h>
#include "Platform.hpp"
#include "Animation.hpp"


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
  void play();
  void pause();
};

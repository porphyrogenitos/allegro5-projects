#pragma once

#include <memory>
#include "Animation.hpp"
#include "Canvas.hpp"
#include "Frame.hpp"
#include "Globals.hpp"

//TODO: InputManager of some sort?

class Application {
private:
  std::unique_ptr<Canvas> canvas;
  std::unique_ptr<Animation> animation;
  std::unique_ptr<Frame> cur_frame;

public:
  Application();
  void draw();
  void tick();
};

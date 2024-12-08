#pragma once

#include <iostream>
#include <utility>
#include <unordered_set>
#include <memory>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "CanvasController.hpp"
#include "Globals.hpp"
#include "Platform.hpp"


class Application {
private:
  ALLEGRO_TIMER* timer;
  ALLEGRO_EVENT_QUEUE* event_queue;
  ALLEGRO_DISPLAY* display;
  ALLEGRO_EVENT event {};

  std::unique_ptr<Platform> platform;
  std::unique_ptr<CanvasController> canvas_controller;

  void init();

  void deinit();
public:
  Application();

  void tick();

  void draw();
};

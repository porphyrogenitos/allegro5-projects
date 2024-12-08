#include "CanvasController.hpp"
#include "Globals.hpp"

CanvasController::CanvasController(Platform* platform) {
  this->platform = platform;
  animation = std::make_unique<Animation>(FPS, FRAME_WIDTH, FRAME_HEIGHT);
  cur_frame = animation->get_cur_frame();
  canvas = std::make_unique<Canvas>(platform, Pixel {0, 0}, CANVAS_WIDTH, CANVAS_HEIGHT, &cur_frame);
  is_playing = false;
}

void CanvasController::draw() {
  canvas->draw();
}

void CanvasController::tick() {
  //If is_playing, move one frame left (or wrap around to frame 0 if reached ending
  if (is_playing) {
    animation->next_frame();
    return;
  }

  // Respond to inputs
  
  canvas->tick();
  
  //Else If keyboard right arrow tapped, move one frame right
  if (platform->keyboard_manager.key_was_pressed(ALLEGRO_KEY_RIGHT)) {
    animation->next_frame();
  }

  //Else If keyboard left arrow tapped, move one frame left
  else if (platform->keyboard_manager.key_was_pressed(ALLEGRO_KEY_LEFT)) {
    animation->prev_frame();
  }
}

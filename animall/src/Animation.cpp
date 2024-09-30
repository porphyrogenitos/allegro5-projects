#include "Animation.hpp"


Animation::Animation() : Animation::Animation(24, 50, 50){}

Animation::Animation(int FPS, int frame_width, int frame_height) {
  this->frame_width = frame_width;
  this->frame_height = frame_height;
  frames.push_back(Frame(frame_width, frame_height)); // TODO: Use constant variables instead of hard coding
  this->FPS = FPS;
  index = 0;
}

Frame Animation::next_frame() {
  if (index == frames.size() - 1) {
    index = 0;
  }
  else {
    index++;
  }

  return this->frames[index];
}

Frame Animation::prev_frame() {
  if (index > 0) {
    index--;
  }

  return frames[index];
}

Frame Animation::get_cur_frame() {
  return frames[index];
}

void Animation::update_cur_frame(Frame new_frame) {
  frames[index] = new_frame;
}

void Animation::insert_blank_frame() {
  if (index == frames.size() - 1) {
    frames.push_back(Frame(this->frame_width, this->frame_height));
  }
  else {
    frames.insert(frames.begin() + index, Frame(this->frame_width, this->frame_height));
  }
}

void Animation::clear_frame() {
  frames[index].set_all(false);
}

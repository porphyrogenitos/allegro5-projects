#include "Animation.hpp"


Animation::Animation() : Animation::Animation(24, 50, 50){}

Animation::Animation(int FPS, int frame_width, int frame_height) {
  this->frame_width = frame_width;
  this->frame_height = frame_height;
  frames.push_back(Frame(frame_width, frame_height)); // TODO: Use constant variables instead of hard coding
  this->FPS = FPS;
  index = 0;
}

Frame& Animation::next_frame() {
  if (index == frames.size() - 1) {
    frames.push_back(Frame(this->frame_width, this->frame_height));
  }

  index++;

  return frames.at(index);
}

Frame& Animation::prev_frame() {
  if (index > 0) {
    index--;
  }

  return frames.at(index);
}

Frame& Animation::get_cur_frame() {
  return frames.at(index);
}

Frame& Animation::insert_frame() {
  frames.insert(frames.begin() + index, Frame(this->frame_width, this->frame_height));
  return frames.at(index);
}

void Animation::clear_frame() {
  frames.at(index).set_all(false);
}

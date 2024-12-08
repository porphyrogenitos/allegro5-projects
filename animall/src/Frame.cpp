#include <iostream>
#include "Frame.hpp"

Frame::Frame(int width, int height) {
  this->width = width;
  this->height = height;
  bitmap.resize(width * height);
  
  for (int i = 0; i < width * height; i++) {
    bitmap.push_back(false);
  }
}

Frame::Frame() : Frame::Frame(100, 100) {}

/*
  Sets bitmap to val at bit (x, y)

  Note: (0, 0) is top left of bitmap
*/
void Frame::set(const Bit& bit, bool val) {
  bitmap[width * bit.x + bit.y] = val;
}

void Frame::set_all(bool val) {
  Bit bit {};
  for (int i = 0; i < width * height; i++) {
    bitmap[i] = val;
  }
}

bool Frame::get(const Bit& bit) {
  return bitmap[width * bit.x + bit.y];
}

int Frame::get_width() {
  return width;
}

void Frame::print() {
  Bit bit {};
  for (bit.y = 0; bit.y < height; bit.y++) {
    for (bit.x = 0; bit.x < width; bit.x++) {
      std::cout << get(bit) << ", ";
    }
    std::cout << "\n";
  }
  
}

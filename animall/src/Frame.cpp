#include <iostream>
#include "Frame.hpp"

Frame::Frame(int width, int height) {
  this->width = width;
  this->height = height;
  
  for (int i = 0; i < height; i++) {
    bitmap.push_back(std::vector<bool>(width, false));
  }
}

/*
  Sets bitmap to val at bit (x, y)

  Note: (0, 0) is top left of bitmap
*/
void Frame::set(int x, int y, bool val) {
  bitmap[x][y] = val;
}

bool Frame::get(int x, int y) {
  return bitmap[x][y];
}

int Frame::get_width() {
  return width;
}

void Frame::print() {
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
      std::cout << get(r, c) << ", ";
    }
    std::cout << "\n";
  }
  
}

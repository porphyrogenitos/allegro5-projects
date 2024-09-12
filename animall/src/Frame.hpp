#pragma once

#include <vector>
#include <memory>

class Frame {
private:
  int width {};
  int height {};
  std::vector<std::vector<bool>> bitmap {};
  //TODO: A variable for indicating whether the frame is on 2s, 3s, etc.

public:
  Frame(int width, int height);
  void set(int x, int y, bool val);
  void set_all(bool val);
  bool get(int x, int y);
  int get_width();
  void print();
};

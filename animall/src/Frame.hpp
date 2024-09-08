#pragma once

#include <vector>
#include <memory>

class Frame {
private:
  int width {};
  int height {};
  std::vector<std::vector<bool>> bitmap {};

public:
  Frame(int width, int height);
  void set(int x, int y, bool val);
  bool get(int x, int y);
  int get_width();
  void print();
};

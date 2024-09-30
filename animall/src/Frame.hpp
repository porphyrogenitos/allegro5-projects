#pragma once

#include <utility>
#include <vector>
#include <memory>

struct Bit {
  int x {};
  int y {};
};

class Frame {
private:
  int width {};
  int height {};
  std::vector<std::vector<bool>> bitmap {};
  //TODO: A variable for indicating whether the frame is on 2s, 3s, etc.

public:
  Frame(int width, int height);
  Frame();
  void set(const Bit& bit, bool val);
  void set_all(bool val);
  bool get(const Bit& bit);
  int get_width();
  void print();
};

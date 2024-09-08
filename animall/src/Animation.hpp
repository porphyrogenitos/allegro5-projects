#pragma once

#include <vector>
#include "Frame.hpp"

class Animation {
private:
  int FPS {};
  std::vector<Frame> frames {};
  int index {};
  
public:
  Frame* next_frame();
  Frame* prev_frame();
  Frame* get_cur_frame();
  Frame* add_frame();
  void clear_frame();
};

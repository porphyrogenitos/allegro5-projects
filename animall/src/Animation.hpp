#pragma once

#include <vector>
#pragma once

#include "Frame.hpp"

class Animation {
private:
  int FPS {};
  std::vector<Frame> frames {};
  int frame_width {};
  int frame_height {};
  int index {};
  
public:
  Animation();
  Animation(int FPS, int frame_width, int frame_height);
  
  Frame& next_frame();
  Frame& prev_frame();
  Frame& get_cur_frame();
  Frame& insert_frame();
  void clear_frame();
};

#pragma once

#include <vector>
#pragma once

#include "Frame.hpp"

class Animation {
private:
  int FPS {};
  std::vector<Frame> frames {};
  //Frame& current_frame; //TODO: Make this a pointer
  int frame_width {};
  int frame_height {};
  int index {};
  
public:
  Animation();
  Animation(int FPS, int frame_width, int frame_height);

  // TODO: Make these return pointers instead of lvalue references. I'm getting segfaults by using lvalue references.
  Frame next_frame();
  Frame prev_frame();
  Frame get_cur_frame();
  void update_cur_frame(Frame new_frame);
  void insert_blank_frame();
  void clear_frame();
};

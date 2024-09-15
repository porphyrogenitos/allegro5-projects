#include <iostream>
#include "Frame.hpp"
#include "Canvas.hpp"
#include "Animation.hpp"

int main() {
  std::cout << "A frame\n";
  Frame frame {20, 20};
  frame.set(5, 2, true);
  frame.print();

  Canvas canvas {0, 0, 100, 100, &frame};
  
  Animation anim {24, 20, 20};

  std::cout << "Animation frame 0\n";
  Frame f = anim.get_cur_frame();
  f.print();
  f.set(2, 3, true);
  anim.update_cur_frame(f);
  std::cout << "Animation frame after modification\n";
  anim.get_cur_frame().print();

  std::cout << "Go to next frame\n";
  Frame f2 = anim.next_frame();
  f2.set_all(true);


  std::cout << "After setting\n";
  anim.update_cur_frame(f2);
  anim.get_cur_frame().print();

  anim.clear_frame();
  std::cout << "After clearing\n";
  anim.get_cur_frame().print();

  std::cout << "Go to prev frame (0)\n";
  Frame f3 = anim.prev_frame();
  anim.get_cur_frame().print();
}

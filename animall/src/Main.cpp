#include <iostream>
#include "Frame.hpp"
#include "Canvas.hpp"
#include "Animation.hpp"

int main() {
  Frame frame {20, 20};
  frame.set(5, 2, true);
  frame.print();

  Canvas canvas {0, 0, 100, 100, &frame};
  
  Animation anim {24, 50, 50};

  std::cout << "Animation frame\n";
  Frame& f = anim.next_frame();
  f.print();
  f.set(2, 3, true);
  std::cout << "Animation frame after modification\n";
  f.print();
  f = anim.next_frame();
  std::cout << "Next frame\n";
  f.print();
  f = anim.prev_frame();
  std::cout << "Prev frame\n";
  f.print();
  std::cout << "Prev frame\n";
  anim.prev_frame().print();
  anim.get_cur_frame().set(2, 3, true);
  anim.get_cur_frame().set(9, 9, true);
  std::cout << "After setting\n";
  anim.get_cur_frame().print();

  anim.clear_frame();
  std::cout << "After clearing\n";
  anim.get_cur_frame().print();
}

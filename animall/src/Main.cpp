#include "Frame.hpp"
#include "Canvas.hpp"

int main() {
  Frame frame {20, 20};
  frame.set(5, 2, true);
  frame.print();

  Canvas canvas {0, 0, 100, 100, &frame};
}
